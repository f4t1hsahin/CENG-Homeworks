#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
import copy

def euclidian_distance(x1, x2):
    #return manhattan_distance(x1,x2)
    x1 = np.array(x1)
    x2 = np.array(x2)
    return np.linalg.norm(x1-x2)**2



class MyKMedoids:
    """KMedoids implementation parametric with 'pam' and 'clara' methods.

    Parameters
    ----------
    n_clusters : int, optional, default: 3
        The number of clusters to form as well as the number of medoids to
        determine.
    max_iter : int, default: 300
        Maximum number of iterations of the k-medoids algorithm for a
        single run.
    method : string, default: 'pam'
        If it is pam, it applies pam algorithm to whole dataset 'pam'.
        If it is 'clara' it selects number of samples with sample_ratio and applies
            pam algorithm to the samples. Returns best medoids of all trials
            according to cost function.
    sample_ratio: float, default: .2
        It is used if the method is 'clara'
    clara_trials: int, default: 10,
        It is used if the method is 'clara'
    random_state : int, RandomState instance or None, optional, default: None
        If int, random_state is the seed used by the random number generator;
        If RandomState instance, random_state is the random number generator;
        If None, the random number generator is the RandomState instance used
        by `np.random`.

    Examples

    """

    def __init__(self, n_clusters=3, max_iter=300, method='pam', sample_ratio=.2, clara_trials=10, random_state=0):
        self.n_clusters = n_clusters
        self.max_iter = max_iter
        self.method = method
        self.sample_ratio = sample_ratio
        self.clara_trials = clara_trials
        self.random_state = random_state
        self.best_medoids = []
        self.min_cost = float('inf')
        if random_state == None:
             self.random = np.random.RandomState(None)
        elif type(random_state) == int:
            self.random = np.random.RandomState(self.random_state)
        else:
            self.random = random_state
        self.X = np.array([])

    def fit(self, X):
        """Compute k-medoids clustering. If method is 'pam'
        Parameters
        ----------
        X : array-like, shape=(n_samples, n_features)
            Training instances to cluster.
        Returns
        ----------
        self : MyKMedoids
        """
        self.X = X
        min_cost = np.inf
        best_medoids = []
        if self.method == 'clara':
            for trial in range(self.clara_trials):
                #print "Iteration ", trial
                samples = self.sample()
                #print "Selected samples: ", samples
                temp_medoids, temp_cost = self.pam(samples)
                #print "Sample best medoids:  ", temp_medoids
                #print "Sample min cost: ", temp_cost
                clusters  = self.generate_clusters(temp_medoids,X)
                cost = self.calculate_cost(temp_medoids, clusters)
                if cost < min_cost:
                    min_cost = cost
                    best_medoids = temp_medoids
                #print "Entire dataset cost: ", cost
                #print "**" * 10
        else:
            best_medoids, min_cost = self.pam(X)
        self.best_medoids = best_medoids
        self.min_cost = min_cost



    def sample(self):
        """Samples from the data with given sample_ratio.

        Returns
        -------
        X : {array-like, sparse matrix}, shape = [n_samples, n_features]
            New data to transform.
        """
        choose_num = int(self.sample_ratio * self.X.shape[0])
        sample_indices = self.random.choice(self.X.shape[0], choose_num, replace=False)
        samples = []
        for sample_index in sample_indices:
            samples.append(self.X[sample_index])
        return np.array(samples)
        

    def pam(self, X):
        """
        kMedoids - PAM
        See more : http://en.wikipedia.org/wiki/K-medoids
        The most common realisation of k-medoid clustering is the Partitioning Around Medoids (PAM) algorithm and is as follows:[2]
        1. Initialize: randomly select k of the n data points as the medoids
        2. Associate each data point to the closest medoid. ("closest" here is defined using any valid distance metric, most commonly Euclidean distance, Manhattan distance or Minkowski distance)
        3. For each medoid m
            For each non-medoid data point o
                Swap m and o and compute the total cost of the configuration
        4. Select the configuration with the lowest cost.
        5. repeat steps 2 to 4 until there is no change in the medoid.
        Parameters
        ----------
        X : {array-like, sparse matrix}, shape = [n_samples, n_features]
            New data to transform.
        Returns
        -------
        best_medoids, min_cost : tuple, shape [n_samples,]
            Best medoids found and the cost according to it.
        """
        medoids = []
        indexes = self.random.choice(X.shape[0], self.n_clusters, replace=False)
        for index in indexes:
            val = X[index].tolist()
            medoids.append(val)
        #print "Start medoids:  ", medoids
        for _iter in range(self.max_iter):
            #print "Iter:  ",  _iter
            #print "Start medoids:  ", medoids
            clusters = self.generate_clusters(medoids, X)
            #print "First Cluster values:  ", clusters[0]
            #print "Second Cluster values:  ", clusters[1]
            cost = self.calculate_cost(medoids, clusters)
            #print medoids,cost
            previous_medoids = copy.deepcopy(medoids)
            for medoid_index in range(self.n_clusters):
                min_cost = self.calculate_cost(medoids, clusters)
                min_index = -1
                #print "Start cost:  ", min_cost
                for element_index in range(len(clusters[medoid_index])):
                    #print type(medoids)
                    #print type(clusters[medoid_index][element_index])
                    #print "Real Medoid:  ", medoids[medoid_index]
                    #print "Temp Medoid:  ", clusters[medoid_index][element_index]
                    if medoids[medoid_index] == clusters[medoid_index][element_index]:
                        continue
                    medoids[medoid_index], clusters[medoid_index][element_index] = clusters[medoid_index][element_index], medoids[medoid_index]
                    temp_cost = self.calculate_cost(medoids, clusters)
                    #print "Temp cost:  of ", medoids[medoid_index]," is " ,temp_cost
                    #print "Elements:  ", clusters[medoid_index]
                    if temp_cost < min_cost:
                        min_cost = temp_cost
                        min_index = element_index
                    medoids[medoid_index], clusters[medoid_index][element_index] = clusters[medoid_index][element_index], medoids[medoid_index]
                    #print "***"*10
                    #print "Real Medoid: ", medoids[medoid_index]

                #print min_cost, min_index
                if min_index != -1:
                    medoids[medoid_index], clusters[medoid_index][min_index] = clusters[medoid_index][min_index], medoids[medoid_index]

            break_loop = True
            #print "Previous Medoids:  ", previous_medoids
            #print "Updated Medoids:   ", medoids
            for i in range(self.n_clusters):
                if previous_medoids[i] != medoids[i]:
                    break_loop = False

            if break_loop == True:
                break

        clusters = self.generate_clusters(medoids, X)
        ret_cost = self.calculate_cost(medoids, clusters)
        return (medoids, ret_cost)


    def generate_clusters(self, medoids, samples):
        """Generates clusters according to distance to medoids. Order
        is same with given medoids array.
        Parameters
        ----------
        medoids: array_like, shape = [n_clusters, n_features]
        samples: array-like, shape = [n_samples, n_features]
        Returns
        -------
        clusters : array-like, shape = [n_clusters, elemens_inside_cluster, n_features]
        """

        print "INSIDE  ", self.n_clusters
        print "Samples ", samples
        n_samples = samples.shape[0]
        result = []
        for i in range(self.n_clusters):
            result.append([])
        for sample_index in range(n_samples):
            sample = samples[sample_index]
            distances = []
            #print "Sample:  ", sample
            for cluster_index in range(self.n_clusters):

                dist =  euclidian_distance(sample, medoids[cluster_index])
                distances.append(dist)
            #print "Distances:  ", distances
            min_index = distances.index(min(distances))
            result[min_index].append(sample.tolist())
        print "RES", result
        print "Clusters ", medoids

        return result

    def calculate_cost(self, medoids, clusters):
        """Calculates cost of each medoid's cluster with squared euclidean function.
        Parameters
        ----------
        medoids: array_like, shape = [n_clusters, n_features]
        clusters: array-like, shape = [n_clusters, elemens_inside_cluster, n_features]
        Returns
        -------
        cost : float
            total cost of clusters
        """
        cost = 0.0
        for cluster_index in range(self.n_clusters):
            cost_of_cluster = 0.0
            for element_index in range(len(clusters[cluster_index])):
                cost_of_cluster += euclidian_distance(clusters[cluster_index][element_index], medoids[cluster_index])
            cost += cost_of_cluster

        return cost
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
        medoids = self.best_medoids
        sample_size = X.shape[0]
        labels = [0] * sample_size
        for sample_index in range(sample_size):
            distances = []
            for medoid_index in range(self.n_clusters):
                val = euclidian_distance(X[sample_index,:],medoids[medoid_index])
                distances.append(val)
            min_index = distances.index(min(distances))
            labels[sample_index] = min_index
        return labels

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
        tt = self.predict(X)
        return np.array(tt)


if __name__ == "__main__":
    X = np.array([np.array([2., 6.]),
                  np.array([3., 4.]),
                  np.array([3., 8.]),
                  np.array([4., 7.]),
                  np.array([6., 2.]),
                  np.array([6., 4.]),
                  np.array([7., 3.]),
                  np.array([7., 4.]),
                  np.array([8., 5.]),
                  np.array([7., 6.])
                  ])

    kmedoids = MyKMedoids(n_clusters=2, random_state=0)
    print kmedoids.fit_predict(X)
    # [1 1 1 1 0 0 0 0 0 0]
    print kmedoids.best_medoids
    # [array([7., 4.]), array([2., 6.])]
    print kmedoids.min_cost
    # 28.0
    #kmedoids2 = MyKMedoids(method='clara', n_clusters=2, sample_ratio=.5, clara_trials = 10, max_iter=300, random_state=0)
    
    #print kmedoids2.fit_predict(X)
    #print kmedoids.best_medoids
    #print kmedoids.min_cost

