#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np

EPSILON = 0.0001

def euclidian_distance(x1, x2):
	x1 = np.array(x1)
	x2 = np.array(x2)
	return np.linalg.norm(x1-x2)




class MyKMeans:
    """K-Means clustering similar to sklearn 
    library but different.
    https://goo.gl/bnuM33

    But still same.

    Parameters
    ----------
    n_clusters : int, optional, default: 8
        The number of clusters to form as well as the number of
        centroids to generate.
    init_method : string, optional, default: 'random'
        Initialization method. Values can be 'random', 'kmeans++'
        or 'manual'. If 'manual' then cluster_centers need to be set.
    max_iter : int, default: 300
        Maximum number of iterations of the k-means algorithm for a
        single run.
    random_state : int, RandomState instance or None, optional, default: None
        If int, random_state is the seed used by the random number generator;
        If RandomState instance, random_state is the random number generator;
        If None, the random number generator is the RandomState instance used
        by `np.random`.
    cluster_centers : np.array, used only if init_method is 'manual'.
        If init_method is 'manual' without fitting, these values can be used
        for prediction.
    """

    def __init__(self, init_method="random", n_clusters=3, max_iter=300, random_state=None, cluster_centers=[]):
        self.init_method = init_method
        self.n_clusters = n_clusters
        self.max_iter = max_iter
        self.random_state = np.random.RandomState(random_state)
        if init_method == "manual":
            self.cluster_centers = cluster_centers
        else:
            self.cluster_centers = []
        self.labels = []

    def fit(self, X):
        """Compute k-means clustering.
        Parameters
        ----------
        X : array-like, shape=(n_samples, n_features)
            Training instances to cluster.
        Returns
        ----------
        self : MyKMeans
        """

        for _iter in range(self.max_iter):
        	cluster_classes = {}
        	for i in range(self.n_clusters):
        		cluster_classes[i] = []
        	for data in X:
        		dists = []
        		for cluster_num in range(self.n_clusters):
        			val = euclidian_distance(self.cluster_centers[cluster_num], data)
        			dists.append(val)
        		min_index = dists.index(min(dists))
        		cluster_classes[min_index].append(data)
        	previous_cluster_centers = self.cluster_centers
        	for i in range(self.n_clusters):
        		lst = cluster_classes[i]
        		if lst != []:
        			self.cluster_centers[i] = np.average(lst, axis = 0)
        	continue_run = [0] * self.n_clusters
        	for i in range(self.n_clusters):
        		if euclidian_distance(self.cluster_centers[i], previous_cluster_centers[i]) > EPSILON:
        			continue_run[i] = 1
        	if sum(continue_run) == 0:
        		break
        for i in range(X.shape[0]):
        	data = X[i]
        	dists = []
        	for cluster_num in range(self.n_clusters):
    			val = euclidian_distance(self.cluster_centers[cluster_num], data)
    			dists.append(val)
    		min_index = dists.index(min(dists))
    		self.labels.append(min_index)
        
        self.labels = np.array(self.labels)




    def initialize(self, X):
        """ Initialize centroids according to self.init_method
        Parameters
        ----------
        X : array-like, shape=(n_samples, n_features)
            Training instances to cluster.
        Returns
        ----------
        self.cluster_centers : array-like, shape=(n_clusters, n_features)
        """
        if self.init_method == 'random':
            indexes = self.random_state.choice(X.shape[0], self.n_clusters, replace=False)
            #print "Indices:  ", indexes 
            for index in indexes:
                val = X[index].tolist()
                self.cluster_centers.append(val)
        elif self.init_method == 'kmeans++': #change according to random choice of other cluster centers
            first_cluster_index = self.random_state.choice(X.shape[0], 1)
            #print "First cluster index:  " , first_cluster_index
            #print X[first_cluster_index][0]
            val = X[first_cluster_index][0].tolist() #check later
            #print val
            self.cluster_centers.append(val)
            #print X
            mask = np.ones(X.shape[0], dtype='bool')
            mask[first_cluster_index] = False
            X = X[mask]
            #print X
            for i in range(1, self.n_clusters):
                    all_distances = []
                    for cluster_num in range(len(self.cluster_centers)):
                            distances = []
                            for data_index in range(X.shape[0]):
                                    dist = euclidian_distance(X[data_index], self.cluster_centers[i - 1])
                                    distances.append(dist)
                            all_distances.append(distances)
                    total_dists = [0] * X.shape[0]
                    for data_index in range(X.shape[0]):
                            val = 0
                            for cluster_num in range(len(self.cluster_centers)):
                                    val += all_distances[cluster_num][data_index]
                            total_dists[data_index] = float(val)
                    max_index = total_dists.index(max(total_dists))
                    val = X[max_index].tolist()
                    self.cluster_centers.append(val)
                    mask = np.ones(X.shape[0], dtype='bool')
                    mask[max_index] = False
                    X = X[mask]
        else:
        	pass
        return self.cluster_centers

    def predict(self, X):
        """Predict the closest cluster each sample in X belongs to.
        In the vector quantization literature, `cluster_centers` is called
        the code book and each value returned by `predict` is the index of
        the closest code in the code book.
        Parameters
        ----------
        X : array-like, shape = [n_samples, n_features]
            New data to predict.
        Returns
        -------
        labels : array, shape [n_samples,]
            Index of the cluster each sample belongs to.
        """
        labels = [0] * len(X)
        for index in range(len(X)):
        	data = X[index]
        	dists = []
        	for cluster_num in range(self.n_clusters):
        		val = euclidian_distance(data, self.cluster_centers[cluster_num])
        		dists.append(val)
        	min_index = dists.index(min(dists))
        	labels[index] = min_index
        return np.asarray(labels)

    def fit_predict(self, X):
        """Compute cluster centers and predict cluster index for each sample.
        Convenience method; equivalent to calling fit(X) followed by
        predict(X).
        Parameters
        ----------
        X : {array-like, sparse matrix}, shape = [n_samples, n_features]
            New data to transform.
        Returns
        -------
        labels : array, shape [n_samples,]
            Index of the cluster each sample belongs to.
        """
        self.fit(X)
        return self.predict(X)


if __name__ == "__main__":
    if __name__ == "__main__":
        X = np.array([[1, 2], [1, 4], [1, 0],
                      [4, 2], [4, 4], [4, 0]])
        kmeans = MyKMeans(n_clusters=2, random_state=0, init_method='kmeans++')
        print kmeans.initialize(X)
        #kmeans.fit(X)
        #print kmeans.cluster_centers

        # [[4. 4.]
        #  [1. 0.]]
        kmeans = MyKMeans(n_clusters=2, random_state=0, init_method = 'random')
        print kmeans.initialize(X)
        # [[4. 0.]
        #  [1. 0.]]
        kmeans.fit(X)
        print kmeans.labels
        #print kmeans.cluster_centers
        # array([1, 1, 1, 0, 0, 0])
        print kmeans.predict([[0, 0], [4, 4]])
        # array([1, 0])
        print kmeans.cluster_centers
        # array([[4, 2],
        #       [1, 2]])