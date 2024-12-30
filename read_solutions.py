import numpy   as np

data=[]
with open("solutions_final.dat") as f:
 for line in f:
  row = line.split()
  data.append(row)
  solution= np.reshape(np.array((row)),(10,6))
  print(solution)
  print('-------')
