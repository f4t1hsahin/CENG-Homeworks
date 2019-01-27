#!/usr/bin/env python
# -*- coding: utf-8 -*-
import numpy as np
import copy
import heapq
from collections import Counter

def euclidian_distance(x1, x2):
    x1 = np.array(x1)
    x2 = np.array(x2)
    return np.linalg.norm(x1-x2)

def manhattan_distance(x1, x2):
    x1 = np.array(x1)
    x2 = np.array(x2)
    return np.sum(x1) - np.sum(x2)

def f(x):
	return x.index(max(x))

class MyKNeighborsClassifier:
    """Classifier implementing the k-nearest neighbors vote similar to sklearn 
    library but different.
    https://goo.gl/Cmji3U

    But still same.
    
    Parameters
    ----------
    n_neighbors : int, optional (default = 5)
        Number of neighbors to use by default.
    method : string, optional (default = 'classical')
        method for voting. Possible values:
        - 'classical' : uniform weights.  All points in each neighborhood
          are weighted equally.
        - 'weighted' : weight points by the inverse of their distance.
          in this case, closer neighbors of a query point will have a
          greater influence than neighbors which are further away.
        - 'validity' weights are calculated with distance and multiplied
          of validity for each voter.  
        Note: implementing kd_tree is bonus.
    norm : {'l1', 'l2'}, optional (default = 'l2')
        Distance norm. 'l1' is manhattan distance. 'l2' is euclidean distance.
    Examples
    --------
    """
    def __init__(self, n_neighbors=5, method='classical', norm='l2'):
        self.n_neighbors = n_neighbors
        self.method = method
        self.norm = norm
        self.labels = []
        self.distinct_labels = []
        self.data = []
        if norm == 'l2':
            self.dist_function = euclidian_distance
        else:
            self.dist_function = manhattan_distance
        self.validity_values = []

    def fit(self, X, y):
        """Fit the model using X as training data and y as target values
        Parameters
        ----------
        X : array-like, shape (n_query, n_features),
            Training data. 
        y : array-like, shape = [n_samples] 
            Target values.
        """
        self.data = X
        self.labels = y
        self.distinct_labels = np.unique(y)
        self.validity_values = [0] * len(X)
        #print "vals", self.validity_values
        if self.method == 'validity':
        	for data_index in range(len(X)):
        		data = X[data_index]
        		label = y[data_index]
        		#print data, label
        		dists = [0] * len(X)
        		for index in range(len(X)):
        			if index == data_index:
        				dists[index] = float('Inf')
        			else:
        				val = self.dist_function(data, X[index])
        				dists[index] = val
        		#print dists
        		smallest_n = []
	    		temp_dists = copy.deepcopy(dists)
	    		_neighbors = []
	    		_labels = []
	    		_dists = []
	    		prev_val = -1
	    		prev_count = 0
	    		for i in range(self.n_neighbors):
	    			val = min(temp_dists)
	    			if prev_val == val:
	    				prev_count += 1
	    			else:
	    				prev_count = 0
	    			indices = [j for j in range(len(dists)) if dists[j] == val]
	    			if len(indices) == 1:
	    				index = indices[0]
	    			else:
	    				index = indices[prev_count]
	    			_dists.append(dists[index])
	    			_neighbors.append(self.data[index])
	    			_labels.append(self.labels[index])
	    			temp_dists.remove(val)
	    			prev_val = val
	    		#print "neighbors of ", data ,"is ",_neighbors
	    		lst = []
	    		for i in range(len(self.distinct_labels)):
	    			lst.append([])
	    		for i in range(self.n_neighbors):
	    			#print "neighbor is", _neighbors[i]
	    			#print "distance and label are", _dists[i], _labels[i]
	    			val = 1. / (_dists[i] + 1e-15)
	    			lst[_labels[i]].append(val)
	    		lst = map(sum, lst)
	    		l1_norm = sum(lst)
	    		for i in range(len(lst)):
	    			lst[i] = lst[i] / float(l1_norm)
	    		#print "list is", lst
	    		self.validity_values[data_index] = lst[label]

		#print "vals", self.validity_values



        
            
    def predict(self, X):
        """Predict the class labels for the provided data
        Parameters
        ----------
        X : array-like, shape (n_query, n_features),
            Test samples.
        Returns
        -------
        y : array of shape [n_samples]
            Class labels for each data sample.
        """
        output = self.predict_proba(X, self.method)
        res = map(f, output)
        return res
        
    def predict_proba(self, X, method=None):
        """Return probability estimates for the test data X.
        Parameters
        ----------
        X : array-like, shape (n_query, n_features),
            Test samples.
        method : string, if None uses self.method.
        Returns
        -------
        p : array of shape = [n_samples, n_classes]
            The class probabilities of the input samples. Classes are ordered
            by lexicographic order.
        """
        if method == None:
            method = self.method
        output = []
        for data_index in range(len(X)):
            data = X[data_index]
            dists = []
            for neighbor in self.data:
                val = self.dist_function(data, neighbor)
                dists.append(val)
            smallest_n = []
            temp_dists = copy.deepcopy(dists)
            _neighbors = []
            _labels = []
            _dists = []
            prev_val = -1
            prev_count = 0
            for i in range(self.n_neighbors):
                val = min(temp_dists)
                if prev_val == val:
                    prev_count += 1
                else:
                    prev_count = 0
                indices = [j for j in range(len(dists)) if dists[j] == val]
                if len(indices) == 1:
                    index = indices[0]
                else:
                    index = indices[prev_count]
                _dists.append(dists[index])
                _neighbors.append(self.data[index])
                _labels.append(self.labels[index])
                temp_dists.remove(val)
                prev_val = val
            #print "neighbors ", _neighbors
            #print "labels ", _labels
            if method == 'classical':
                temp = [0] * len(self.distinct_labels)
                for _label in _labels:
                    temp[_label] += 1
                #print temp
                for i in range(len(self.distinct_labels)):
                    temp[i] = float(temp[i]) / len(_labels)
                output.append(temp)
            if method == 'weighted':
                lst = []
                for i in range(len(self.distinct_labels)):
                    lst.append([])
                for i in range(self.n_neighbors):
                    val = 1. / (_dists[i] + 1e-15)
                    lst[_labels[i]].append(val)
                lst = map(sum, lst)

                total = sum(lst)
                for i in range(len(lst)):
                    lst[i] = float(lst[i])/total
                output.append(lst)
            if method == 'validity':
                lst = []
                for i in range(len(self.distinct_labels)):
                    lst.append([])
                for i in range(self.n_neighbors):
                    #print "neigbor ", _neighbors[i]
                    #print "validity ", self.validity_values[self.data.index(_neighbors[i])]
                    validity_value = self.validity_values[self.data.tolist().index(_neighbors[i].tolist())]
                    val = validity_value * (1. / (_dists[i] + 1e-15))
                    lst[_labels[i]].append(val)
                lst = map(sum, lst)
                total = sum(lst)
                for i in range(len(lst)):
                    lst[i] = float(lst[i])/total
                output.append(lst)
        #print "OUTPUT", output
        return output

if __name__=='__main__':
    X = [[0], [1], [2], [3]]
    y = [0, 0, 1, 1]
    neigh = MyKNeighborsClassifier(n_neighbors=3, method="validity")
    neigh.fit(X, y)
    n = 0.9
    print(neigh.predict_proba([[0.9]], method='classical'))
    # [[0.66666667 0.33333333]]
    print(neigh.predict_proba([[0.9]], method='weighted'))
    # [[0.75089392 0.24910608]]
    print(neigh.predict_proba([[0.9]], method='validity'))
    # [[0.75697674 0.24302326]]