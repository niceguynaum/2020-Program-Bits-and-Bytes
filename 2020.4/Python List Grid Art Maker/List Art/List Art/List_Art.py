# Task:
# Within an 11x11 grid, create a simple line making tool with slopes. Support up to 2 lines being
# generated

# Setting up an empty list of 11 elements for a grid

x_plane = []
for i in range(11):
    x_plane.append(i)
y_plane = []
for y in range(11):
    y_plane.append(y)

line_1_char = 'x'
line_2_char = 'o'

print("Please enter your slope y, slope x, starting x coordinate, and then starting y coordinate")
slope_y = int(input())
slope_x = int(input())
x_start = int(input())
y_start = int(input())

# print("How many lines would you like to use?")
# lineInput = int(input())
# y = mx + b

# if lineInput == 1:
# if lineInput == 2:

for x in range(x_start, len(x_plane), slope_x):
    x_plane[x] = line_1_char
    for y in range(y_start, len(y_plane), slope_y):
        y_plane[y] = line_1_char

for y in y_plane:
    print(y_plane)
    for x in x_plane:
        print(x_plane)
        
# DEBUG 
# print(slope, x_start, y_start)