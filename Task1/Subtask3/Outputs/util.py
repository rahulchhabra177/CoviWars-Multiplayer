import numpy
import csv
from numpy import genfromtxt
<<<<<<< HEAD
runtimes = [[0,0,0,0,0,0],[0,264,160,147,139,134],[0,274,238,241,244,243],[0,267,267,230,227,224],[0,181,175,178,173,176]]
=======
runtimes = [[0,0,0,0,0,0],[0,344,211,207,200,0],[0,341,345,337,330,0],[0,375,433,354,331,324],[0,300,299,296,297,308]]
>>>>>>> 440e4b3e8df77659515eeff52d08b72463e44b3f
for i in range(1,5):
	with open("utility"+str(i)+".csv", 'w', newline='') as file:

		for j in range(6):
<<<<<<< HEAD
			file1 = "out"+str(i)+str(j)+".csv"
=======
			file1 = "out"+str(i)+str(j)+".csv";
>>>>>>> 440e4b3e8df77659515eeff52d08b72463e44b3f
			if runtimes[i][j]!=0:
				data = genfromtxt(file1,dtype=float,delimiter=',',skip_footer=1)
				origData = genfromtxt("out.csv",dtype=float,delimiter=',',skip_footer=1)

				def utility(data):
<<<<<<< HEAD
					qError= 0.0
					n=data.shape[0]
					for i in range(0,n):
						qError += abs(data[i][1]-origData[i][1])
					if qError==0:
					    return -1
					else:
						return n/qError
=======
				    qError= 0.0
				    dError = 0.0
				    n=data.shape[0]
				    for i in range(0,n):
				        qError += abs(data[i][1]-origData[i][1])
				        dError += abs(data[i][2]-origData[i][2])
				    if qError==0 and dError==0:
				    	return (-1,-1)
				    elif qError==0:
				    	return (-1,n/dError)
				    elif dError==0:
				    	return (n/qError,-1)
				    else:			    
					    qError,dError = n/qError,n/dError
					    return (qError,dError)
>>>>>>> 440e4b3e8df77659515eeff52d08b72463e44b3f

				util=utility(data)

				writer = csv.writer(file)
<<<<<<< HEAD
				writer.writerow([runtimes[i][j],util])
=======
				writer.writerow([runtimes[i][j],util[0], util[1]])
>>>>>>> 440e4b3e8df77659515eeff52d08b72463e44b3f
