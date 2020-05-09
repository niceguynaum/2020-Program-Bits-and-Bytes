#include <iostream>
#include "NoiseMaker.h"

#define OSC_SINE 0
#define OSC_SQUARE 1
#define OSC_TRIANGLE 2
#define OSC_SAW_ANA 3
#define OSC_SAW_DIG 4
#define OSC_NOISE 5

// Converts frequency (Hz) to angular velocity
double w(double dHertz)
{
	return dHertz * 2.0 * PI;
}

double osc(double dHertz, double dTime, int nType = OSC_SINE, double dLFOHertz = 0.0, double dLFOAmplitude = 0.0)
{
	double dFreq = w(dHertz) * dTime + dLFOAmplitude * dHertz * sin(w(dLFOHertz) * dTime);

	switch (nType)
	{
	case OSC_SINE: //Sine wave with small modulation
		return sin(dFreq);
	case OSC_SQUARE: //Square wave
		return sin(dFreq * dTime) > 0.0 ? 1.0 : -1.0;
	case OSC_TRIANGLE: //Triangle Wave
		return asin(sin(dFreq * dTime)) * 2.0 / PI;
	case OSC_SAW_ANA: //Saw Wave (analogue / warm / slow)
	{
		double dOutput = 0.0;

		for (double n = 1.0; n < 100.0; n++)
			dOutput += (sin(n * dFreq)) / n;
		return dOutput * (2.0 / PI);
	}
	case OSC_SAW_DIG: // Saw wave (optimised / harsh/ fast)
		return (2.0 / PI) * (dHertz * PI * fmod(dTime, 1.0 / dHertz) - (PI / 2.0));
	case OSC_NOISE: //Pseudo Random Noise
		return 2.0 * ((double)rand() / (double)RAND_MAX) - 1.0;
	default:
		return 0;
	}
}

struct sEnvelopeADSR
{
	double dAttackTime;
	double dDecayTime;
	double dReleaseTime;
	double dSustainAmplitude;

	double dStartAmplitude;

	double dTriggerOnTime;
	double dTriggerOffTime;

	bool bNoteOn;

	sEnvelopeADSR()
	{
		dAttackTime = 0.01;
		dDecayTime = 0.01;
		dStartAmplitude = 1.0;
		dSustainAmplitude = 0.8;
		dReleaseTime = 0.02;
		dTriggerOnTime = 0.0;
		dTriggerOffTime = 0.0;
		bNoteOn = false;
	}

	double GetAmplitude(double dTime)
	{
		double dAmplitude = 0.0;
		double dLifeTime = dTime - dTriggerOnTime;

		if (bNoteOn)
		{
			// Attack
			if (dLifeTime <= dAttackTime)
				dAmplitude = (dLifeTime / dAttackTime) * dStartAmplitude;

			// Decay
			if (dLifeTime > dAttackTime && dLifeTime <= (dAttackTime + dDecayTime))
				dAmplitude = ((dLifeTime / dAttackTime) / dDecayTime) * (dSustainAmplitude - dStartAmplitude) + dStartAmplitude;

			// Sustain
			if (dLifeTime > (dAttackTime + dDecayTime))
			{
				dAmplitude = dSustainAmplitude;
			}
		}
		else
		{
			// Release
			dAmplitude = ((dTime - dTriggerOffTime) / dReleaseTime) * (0.0 - dSustainAmplitude) + dSustainAmplitude;
		}

		if (dAmplitude <= 0.0001)
		{
			dAmplitude = 0;
		}

		return dAmplitude;
	}

	void NoteOn(double dTimeOn)
	{
		dTriggerOnTime = dTimeOn;
		bNoteOn = true;
	}

	void NoteOff(double dTimeOff)
	{
		dTriggerOffTime = dTimeOff;
		bNoteOn = false;
	}


};

sEnvelopeADSR envelope;

struct instrument
{
	double dVolume;
	sEnvelopeADSR env;

	virtual double sound(double dTime, double dFrequencyOutput) = 0;
};

atomic<double> dFrequencyOutput = 0.0;
double dOctaveBaseFrequency = 220.0; //A3
double d12thRootOf2 = pow(2.0, 1.0 / 12.0);

instrument *voice = nullptr;

struct bell : public instrument
{
	bell()
	{
		env.dAttackTime = 0.01;
		env.dDecayTime = 1.0;
		env.dStartAmplitude = 1.0;
		env.dSustainAmplitude = 0.0;
		env.dReleaseTime = 1.0;
	}

	double sound(double dTime, double dFrequency)
	{
		double dOutput = envelope.GetAmplitude(dTime) *
			(
				+ 1.0 * osc(dFrequencyOutput, dTime, OSC_SINE, 5.0, 0.01)
			);

		return dOutput;
	}
};

double MakeNoise(double dTime)
{
	double dOutput = voice->sound(dTime, dFrequencyOutput);
	return dOutput * 0.4; // Master volume
}

int main()
{
	// get all sound hardware
	std::vector<wstring> devices = olcNoiseMaker<short>::Enumerate();

	// Display Findings
	for (auto d : devices) wcout << "Found Output Device:" << d << endl;

	// Create sound machine!!
	olcNoiseMaker<short> sound(devices[0], 44100, 1, 8, 512);
										//SR, #ofChannels, last two numbers determine memory allocation

	voice = new bell();

	// Link noise function with sound machine
	sound.SetUserFunction(MakeNoise);


	int nCurrentKey = -1;
	bool bKeyPressed = false;
	while (1)
	{
		bKeyPressed = false;
		for (int i = 0; i < 15; i++)
		{
			if (GetAsyncKeyState((unsigned char)("ZSXCFVGBNJMK\xbcL\xbe\xbf"[i])) & 0x8000)
			{
				if (nCurrentKey != i)
				{
					dFrequencyOutput = dOctaveBaseFrequency * pow(d12thRootOf2, i);
					voice->env.NoteOn(sound.GetTime());
					wcout << "\rNote On : " << sound.GetTime() << "s " << dFrequencyOutput << "Hz";
					nCurrentKey = i;
				}

				bKeyPressed = true;
			}
		}
		if (!bKeyPressed)
		{
			if (nCurrentKey != -1)
			{
				wcout << "\rNote Off: " << sound.GetTime() << "s                        ";
				voice->env.NoteOff(sound.GetTime());
				nCurrentKey = -1;
			}
		}
	}
	return 0;
}
