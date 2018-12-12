import numpy as np

class OneHotEncoder:
    def __init__(self):
        self.tags=[]

    def fit(self,X):
        """Converts list of labels into unique list and stores in self.tags.

        :param X: list of labels
        :return: None
        """
        # TODO: Implement this method
        for x in X:
        	self.tags.append(x)
        self.tags = list(set(self.tags))
        

    def fit_transform(self,X):
        """Calls fit and transform methods respectively with X.

        :param X: list of labels
        :return: numpy array of one-hot vectors for each element in X
        """
        # TODO: Implement this method
        self.fit(X)
        return self.transform(X)

    def transform(self, X):
        """Converts each element in the list into their one-hot representations

        :param X: list of labels
        :return: numpy array of one-hot vectors for each element in X
        """
        # TODO: Implement this method
        res = []
        for x in X:
        	temp_res = np.zeros(len(self.tags))
        	try:
	        	index = self.tags.index(x)
	        	temp_res[index] = 1
        		res.append(temp_res)
        	except:
        		res.append(temp_res)
        res = np.array(res)
        return res

    def get_feature_names(self):
        """Returns the tags
        :return: tags
        """
        # TODO: Implement this method
        return self.tags

    def decode(self, one_hot_vector):
        """Decodes given one-hot-vector into its value.

        :param one_hot_vector: numpy array for one-hot-vector
        :return: corresponding element in self.tags
        """
        # TODO: Implement this method
        index = one_hot_vector[one_hot_vector == 1][0]
        return self.tags[index]


if __name__=="__main__":
    o = OneHotEncoder()
    train_labels = ["Action","Comedy","Crime","Comedy","Crime","Musical","Action"]
    test_labels = ["Comedy","Action","Crime","Musical","Crime","War"]
    train_one_hot_vectors = o.fit_transform(train_labels)
    test_one_hot_vectors = o.transform(test_labels) 
    print o.get_feature_names()
    print train_one_hot_vectors
    print test_one_hot_vectors
    one_hot_vector = np.array([0,1,0,0])
    print o.decode(one_hot_vector)
