#!/usr/bin/env python
# -*- coding: utf-8 -*-

from PIL import Image
import numpy as np
from sklearn.utils import shuffle
import matplotlib.pyplot as plt
from MyKMeans import MyKMeans
from sklearn.cluster import KMeans
from collections import Counter

class ColorQuantizer:
    """Quantizer for color reduction in images. Use MyKMeans class that you implemented.
    
    Parameters
    ----------
    n_colors : int, optional, default: 64
        The number of colors that wanted to exist at the end.
    random_state : int, RandomState instance or None, optional, default: None
        If int, random_state is the seed used by the random number generator;
        If RandomState instance, random_state is the random number generator;
        If None, the random number generator is the RandomState instance used
        by `np.random`.

    Read more from:
    http://scikit-learn.org/stable/auto_examples/cluster/plot_color_quantization.html
    """
    
    def __init__(self, n_colors=64, random_state=None):
        self.n_colors = n_colors
        self.random_state = random_state
        self.image_array = np.array([])
        self.w = 0
        self.h = 0
        self.d = 0
    
    def read_image(self, path):
        """Reads jpeg image from given path as numpy array. Stores it inside the
        class in the image variable.
        
        Parameters
        ----------
        path : string, path of the jpeg file
        """
        array = np.asarray(Image.open(path))
        #array = np.array(array, dtype=np.float64) / 255
        w, h, d = original_shape = tuple(array.shape)
        self.w , self.h, self.d = w, h, d
        image_array = np.reshape(array, (w * h, d))
        self.image_array = image_array
        self.cluster_centers = []

    def recreate_image(self, path_to_save):
        """Reacreates image from the trained MyKMeans model and saves it to the
        given path.
        
        Parameters
        ----------
        path_to_save : string, path of the png image to save
        """
        labels = self.labels
        cluster_centers = self.cluster_centers
        out_array = np.zeros((self.w*self.h,self.d))
        for label_index in range(len(labels)):
            out_array[label_index,:] = np.array(cluster_centers[labels[label_index]])
        out_array = out_array.reshape((self.w, self.h, self.d))
        #out_array *= 255
        out_array = out_array.astype('uint8')
        self.out_array = out_array
        #print type(self.out_array)
        img = Image.fromarray(self.out_array)
        img.save(path_to_save)
        

    def export_cluster_centers(self, path):
        """Exports cluster centers of the MyKMeans to given path.

        Parameters
        ----------
        path : string, path of the txt file
        """

        np.savetxt(path,self.cluster_centers)
        
    def quantize_image(self, path,weigths_path, path_to_save):
        """Quantizes the given image to the number of colors given in the constructor.
        
        Parameters
        ----------
        path : string, path of the jpeg file
        """
        self.read_image(path)
        image_array = self.image_array
        #print np.unique(image_array,axis=0).shape
        #exit()
        #tple_array = [tuple(x) for x in image_array]
        #cnt = Counter(tple_array)
        #commons =  cnt.most_common(10000)
        #commons_lists = [list(x[0]) for x in commons]
        #commons_lists = np.array(commons_lists)
        #print commons_lists
        #exit()
        #kmeans = MyKMeans(n_clusters=self.n_colors, random_state=self.random_state, init_method='kmeans++')
        shuffled = shuffle(np.unique(image_array,axis=0), random_state=0)[:100]
        #kmeans.initialize(shuffled)
        #kmeans.fit(shuffled)
        kmeans = MyKMeans(n_clusters=self.n_colors, random_state=self.random_state, max_iter=5,init_method='kmeans++')
        kmeans.initialize(shuffled)
        fit_value = shuffle(np.unique(image_array,axis=0), random_state=0)[:1000]
        kmeans.fit(fit_value)
        self.labels = kmeans.predict(image_array)
        self.cluster_centers = kmeans.cluster_centers
        self.recreate_image(path_to_save)
        self.export_cluster_centers(weigths_path)

if __name__ == "__main__":
	qq = ColorQuantizer(64,0)
	print "Start"
	qq.quantize_image('metu.jpg', 'metu_cluster_centers.txt', 'my_quantized_metu.png')
	print "Second"
	qq.quantize_image('ankara.jpg','ankara_cluster_centers.txt', 'my_quantized_ankara.png')
	