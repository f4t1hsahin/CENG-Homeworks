#!/usr/bin/env python
# -*- coding: utf-8 -*-
import nltk
import numpy as np
import math
from collections import Counter



class Vectorizer:
    def __init__(self, min_word_length=3, max_df=1.0, min_df=0.0):
        self.min_word_length = min_word_length
        self.max_df=max_df
        self.min_df=min_df
        self.term_df_dict = {}
        self.term_index_dict = {}
        self.vocabulary = []
        self.len_vocab = 0

    def fit(self, raw_documents):
        """Generates vocabulary for feature extraction. Ignores words shorter than min_word_length and document frequency
        not between max_df and min_df.

        :param raw_documents: list of string for creating vocabulary
        :return: None
        """
        self.document_count = len(raw_documents)
        # TODO: Implement this method
        for document in raw_documents:
            for token in np.unique(document.split(' ')):
                if len(token) >= self.min_word_length:
                    try:
                        self.term_df_dict[token] += 1
                    except:
                        self.term_df_dict[token] = 1
        print "11"
        index = 0
        for key in self.term_df_dict.keys():
            df = self.term_df_dict[key] / float(self.document_count)
            if df >= self.min_df and df <= self.max_df:
                self.vocabulary.append(key)
                self.term_index_dict[key] = index
                index += 1
            else:
                self.term_df_dict.pop(key)
        print "22"
        self.len_vocab = len(self.vocabulary)


    def _transform(self, raw_document, method):
        """Creates a feature vector for given raw_document according to vocabulary.

        :param raw_document: string
        :param method: one of count, existance, tf-idf
        :return: numpy array as feature vector
        """
        # TODO: Implement this method
        feature_vector = [0] * self.len_vocab
        #feature_vector = np.zeros(10000)
        if method == 'existance':
            for token in raw_document.split(' '):
                if token in self.term_df_dict:
                    index = self.term_index_dict[token]
                    feature_vector[index] = 1
                
        elif method == 'count':
            for token in raw_document.split(' '):
                if token in self.term_df_dict:
                    index = self.term_index_dict[token]
                    feature_vector[index] += 1
        elif method == 'tf-idf':
            rng = raw_document.split(' ')
            cnt = Counter(rng)
            for token in rng:
                if token in self.term_df_dict:
                    cnt_c = cnt[token]
                    idf_without_log = (1.0 + self.document_count) / (self.term_df_dict[token] + 1.0)
                    idf = math.log(idf_without_log) + 1
                    if token in self.term_df_dict:
                        index = self.term_index_dict[token]
                        feature_vector[index] = float(cnt_c) * idf
            c = 0.0
            for x in feature_vector:
                c += x**2
            feature_vector = np.array(feature_vector)
            if c != 0:
                feature_vector /= c**0.5
        return feature_vector

    def transform(self, raw_documents, method="tf-idf"):
        """For each document in raw_documents calls _transform and returns array of arrays.

        :param raw_documents: list of string
        :param method: one of count, existance, tf-idf
        :return: numpy array of feature-vectors
        """
        # TODO: Implement this method
        res = []
        for document in raw_documents:
            res.append(self._transform(document, method))
        res = np.array(res)
        return res
    def fit_transform(self, raw_documents, method="tf-idf"):
        """Calls fit and transform methods respectively.

        :param raw_documents: list of string
        :param method: one of count, existance, tf-idf
        :return: numpy array of feature-vectors
        """
        # TODO: Implement this method
        self.fit(raw_documents)
        ret = self.transform(raw_documents) 
        return ret       

    def get_feature_names(self):
        """Returns vocabulary.

        :return: list of string
        """
        try:
            self.vocabulary
        except AttributeError:
            print "Please first fit the model."
            return []
        return self.vocabulary

    def get_term_dfs(self):
        """Returns number of occurances for each term in the vocabulary in sorted.

        :return: array of tuples
        """
        return sorted(self.term_df_dict.iteritems(), key=lambda (k, v): (v, k), reverse=True)

if __name__=="__main__":
    v = Vectorizer(min_df=.25, max_df=.75)
    contents = [
     "this is the first document",
     "this document is the second document",
     "and this is the third one",
     "is this the first document",
 ]
    v.fit(contents)
    print v.get_feature_names()
    existance_vector = v.transform(contents, method="existance")        
    print existance_vector
    count_vector = v.transform(contents, method="count")        
    print count_vector
    tf_idf_vector = v.transform(contents, method="tf-idf")
    print tf_idf_vector

