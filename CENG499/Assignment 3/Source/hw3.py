import sys
import numpy as np

def forward(transition_matrix, estimate_matrix, observation):
	n = len(transition_matrix)
	t = len(observation)
	#print "State count:  ", n
	#print "Time:  ", t
	forward = np.zeros((n, t + 1))
	for s in range(1,n - 1):
		#print "Transition matrix 0," + str(s) + ":   ", transition_matrix[0][s]
		#print "Estimate matrix "+str(s) +":   ", estimate_matrix[s][observation[0]]
		forward[s,1] = transition_matrix[0][s] * estimate_matrix[s][observation[0]]
	#print forward
	for t in range(2,t + 1):
		for s in range(1,n - 1):
			total = 0
			for ss in range(1, n - 1):
				#print "T: ", t, " S: ", s, " ss: ", ss, " observation:  ", observation[t-1]
				#print "Forward ss, t-1 :  ", forward[ss,t - 1]
				#print "Transition matrix ss, s:  ", transition_matrix[ss][s]
				#print "Estimate matrix s, t:  ", estimate_matrix[s][observation[t - 1]]
				total += forward[ss, t - 1] * transition_matrix[ss][s] * estimate_matrix[s][observation[t-1]]
			forward[s,t] = total
			#print forward

	res = 0.0
	#print forward
	for s in range(1,n - 1):
		#print "S:  ", s
		#print "Forward s, t-1:  ", forward[s, t]
		#print "Transition matrix s, n - 1:  ", transition_matrix[s][-1]
		res += forward[s, t] * transition_matrix[s][-1]
		#print "Multiplication:  ", forward[s, t] * transition_matrix[s][n - 1]
	return res






def viterbi(transition_matrix, estimate_matrix, observation):
	n = len(transition_matrix)
	t = len(observation)
	backpointer = np.zeros((n, t+1))
	#print "State count:  ", n
	#print "Time:  ", t
	viterbi = np.zeros((n, t + 1))
	for s in range(1,n - 1):
		#print "Transition matrix 0," + str(s) + ":   ", transition_matrix[0][s]
		#print "Estimate matrix "+str(s) +":   ", estimate_matrix[s][observation[0]]
		viterbi[s,1] = transition_matrix[0][s] * estimate_matrix[s][observation[0]]
		backpointer[s,1] = 0
	#print viterbi
	for t in range(2,t + 1):
		for s in range(1,n - 1):
			values = []
			values2 = []
			for ss in range(1, n - 1):
				#print "T: ", t, " S: ", s, " ss: ", ss, " observation:  ", observation[t-1]
				#print "Forward ss, t-1 :  ", viterbi[ss,t - 1]
				#print "Transition matrix ss, s:  ", transition_matrix[ss][s]
				#print "Estimate matrix s, t:  ", estimate_matrix[s][observation[t - 1]]
				values.append(viterbi[ss, t - 1] * transition_matrix[ss][s] * estimate_matrix[s][observation[t-1]])
				values2.append(viterbi[ss, t - 1] * transition_matrix[ss][s])
			viterbi[s,t] = max(values)
			backpointer[s,t] = values2.index(max(values2)) + 1
	#print viterbi
	#print backpointer
	res_values = []
	for s in range(1,n - 1):
		#print "S:  ", s
		#print "Forward s, t-1:  ", viterbi[s, t]
		#print "Transition matrix s, n - 1:  ", transition_matrix[s][-1]
		res_values.append(viterbi[s, t] * transition_matrix[s][-1])
		#print "Multiplication:  ", viterbi[s, t] * transition_matrix[s][n - 1]

	viterbi[-1,-1] = max(res_values)
	backpointer[-1, -1] = res_values.index(max(res_values)) + 1

	#print backpointer

	time = t
	result = []
	result.append(int(backpointer[-1,-1]))
	temp_variable = backpointer[-1, -1]
	while time != 0:
		result.insert(0, int(backpointer[ int(temp_variable),time]))
		temp_variable = backpointer[int(temp_variable),time]
		time -= 1
	return map(int,result[1:])
	#print viterbi
	#print "**********" * 5
	#print backpointer


def read_transition_matrix(path):
	f = open(path,'r')
	lines = f.readlines()
	lines = [map(float,line.strip().split()) for line in lines]
	#print lines
	f.close()
	return lines




def read_estimate_matrix(path):
	f = open(path,'r')
	lines = f.readlines()
	lines = [map(float,line.strip().split()) for line in lines]
	f.close()
	#print lines
	return lines




def read_observation(path):
	f = open(path,'r')
	line = f.readlines()[0]
	line = map(int , line.strip().split(' '))
	#print line
	f.close()
	return line




def main():
	observation =  read_observation(sys.argv[4])
	estimate_matrix = read_estimate_matrix(sys.argv[3])
	transition_matrix =  read_transition_matrix(sys.argv[2])
	if sys.argv[1] == 'forward':
		return forward(transition_matrix, estimate_matrix, observation)
	elif sys.argv[1] == 'viterbi':
		return viterbi(transition_matrix, estimate_matrix, observation)





if __name__ == '__main__':
	print main()
