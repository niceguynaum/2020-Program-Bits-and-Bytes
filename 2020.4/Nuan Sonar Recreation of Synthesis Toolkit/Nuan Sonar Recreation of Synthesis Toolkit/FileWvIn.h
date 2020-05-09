#ifndef STK_FILEWVIN_H
#define STK_FILEWVIN_H

#include "WvIn.h"
#include "FileRead.h"

namespace stk {

	class FileWvIn : public WvIn
	{
	public: 
		FileWvIn(unsigned long chunkThreshold = 1000000, unsigned long chunkSize = 1024);

		//! Overloaded constructor for file input.

		/*!
			An StkError will be thrown if the file is not found, its format is unknown, or a read error
			occurs.
		*/
		FileWvIn(std::string fileName, bool raw = false, bool doNormalize = true, unsigned long chunkThreshold = 1000000, 
				unsigned long chunkSize = 1024, bool doInt2FloatScaling = true);

		//! Class destructor.
		~FileWvIn(void);

		virtual void openFile(std::string fileName, bool raw = false, bool doNormalize = true, 
							  bool doInt2FloatScaling = true);

		//! Close a file if one is open.
		virtual void closeFile(void);

		//! Clear outputs and reset time (file) pointer to zero.
		virtual void reset(void);

		//! Normalize data to a maximum of +-1.0.
		/*!
			This function has no effect when data is incrementally loaded from disk.
		*/

		virtual void normalize(void);

		//! Normalize data to a maximum of \e +-peak.
		/*!
			This function has no effect when data is incrementally loaded from disk.
		*/
		virtual void normalize(stk::StkFloat peak);

		//! Return the file size in sample frames.
		virtual unsigned long getSize(void) const { return fileSize_; };

		//! Return the input file sample rate in Hz (not the data read rate).
		/*!
			WAV, SND, and AIF, formatted files specify a sample rate in their headers. 
			STK RAW files have a sample rate of 22050 hz by definition. MAT-files are assumed to have a rate of 44100 Hz.
		
		*/
		virtual stk::StkFloat getFileRate(void) const { return data_.dataRate(); };

		//! Query whether a file is open.
		bool isOpen(void) { return file_.isOpen(); };

		//! Query whether reading is complete.
		bool isFinished(void) const { return finished_; };

		//! Set the data read rate in samples. The rate can be negative.
		/*!
			If the rate value is negative, the data is read in reverse order.
		*/
		virtual void setRate(stk::StkFloat rate);

		//! Increment the read pointer by \e time samples.
		/*!
			Note that this function will not modify the interpolation flag status.	
		*/
		virtual void addTime(stk::StkFloat time);

		//! Turn linear interpolation on/off.
		/*!
			Interpolation is automatically off when the read rate is an integer value.
			If interpolation is turned off for a fractional rate, the time index is truncated to an
			integer value.
		*/
		void setInterpolate(bool doInterpolate) { interpolate_ = doInterpolate; };

		//! Return the specified channel value of the last computed frame.
		/*!
			If no file is laoded, the returned value is 0.0. The \c channel argument must be less
			then the number of output channels, which can be determined with the channelsOut()
			function (the first channel is specified by 0). However, range checking is only preformed
			if _STK_DEBUG_ is defined during compilation, in which case an out-of-range value will
			trigger an StkError exception. \sa lastFrame()
		*/

		StkFloat lastout(unsigned int channel = 0);

		//! Compute a sample frame and return the specified \c channel value.
		/*!
			For multi-channel files, use the lastFrame() function to get all values from the computed
			frame. If no file data is loaded, the returned value is 0.0. The \c channel argument must be
			less than the number of channels in the file data (the first channel is specified by 0). However,
			range checking is only preformed if _STK_DEBUG_ is defined during compilation, in which case an
			out-of-range value will trigger an StkError exception.
		*/
		virtual stk::StkFloat tick(unsigned int channel = 0);

		//! Fill the StkFrames object with computed sample frames, starting at the specified channel
		//! and return the same reference.

		/*
			The \c channel argument plus the number of input channels must be less than the number
			of channels in the StkFrames argument (the first channel is specified by 0). However,
			range checking is only preformed if _STK_DEBUG_ is defined during compilation, in which
			case an out-of-range value will trigger an StkError exception.
		*/
		virtual StkFrames& tick(StkFrames& frames, unsigned int channel = 0);

	protected:

		void sampleRateChanged(StkFloat newRate, StkFloat oldRate);

		FileRead file_;
		bool finished_;
		bool interpolate_;
		bool int2floatscaling_;
		bool chunking_;
		StkFloat time_;
		StkFloat rate_;
		unsigned long fileSize_;
		unsigned long chunkThreshold_;
		unsigned long chunkSize_;
		long chunkPointer_;

	};

	inline StkFloat FileWvIn::lastout(unsigned int channel)
	{
#if defined(_STK_DEBUG_)
		if (channel >= data_.channels()) {
			oStream_ << "FileWvIn::lastOut(): channel argument and soundfile data are incompatable!";
			handleError(Stk::FUNCTION_ARGUMENT);
		}
#endif

		if (finished_) return 0.0;
		return lastFrame_[channel];
	}
}

#endif