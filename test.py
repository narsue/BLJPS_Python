import BL_JPS
from astar import method
import numpy as np
from datetime import datetime

# The following shows the difference between running c++ BLJPS and python A star
# The example is relatively simple a small map of 64x64 with a single obstacle at (3,3)
# The larger the map the greater the speedup BLJPS will have
# Obstacles will slow down the algorithm
# The test runs an example of changing the map once and then running 100 queries 
# (like an rts game where 100 units make a decision every cycle)

# Current results:
# BLJPS 0.001 seconds
# Astar 4.24 seconds

map_width = map_height = 64

map_data = [0]*(map_width*map_height)
map_data[3*map_width + 3] = 1
origin = (3,2)
dest = (63,63)

# BLJPS algorithm
bljps = BL_JPS.BL_JPS(map_data, width=map_width, height=map_height)
start = datetime.now()
bljps.preProcessGrid()
for trial in range(100):
	bljps_path = bljps.findSolution(origin[0], origin[1], dest[0], dest[1])
print ('BL_JPS runtime Seconds:',(datetime.now()-start).total_seconds())
for p in bljps_path:
	print (p[0],p[1])
	
# Note that BLJPS returns a compressed path (jump points)
# Its fairly simple to uncompress
# Each pair of points represents a line for the sequence (0,0), (4,0)
# Uncompress to (0,0), (1,0), (2,0), (3,0), (4,0) 
# Diagonal decompression doubles the size - you can take either horizontal or vertical actions in any order
# Ex: (0,0) -> (2,2) 
# Uncompressed: (0,0), (1,0), (1,1), (2,1), (2,2) (Horizontal movement first)
# Uncompressed: (0,0), (0,1), (1,1), (1,2), (2,2) (Vertical movement first) 
# Both and any other permutation of vertical vs horizontal movements is fine and both represent optimal paths


map_data = np.zeros((map_width,map_height))
map_data[3,3] = 1

start = datetime.now()
for trial in range(100):
	atar_path = method(map_data,dest, origin)
print ('Astar runtime Seconds:',(datetime.now()-start).total_seconds())
print (atar_path)
