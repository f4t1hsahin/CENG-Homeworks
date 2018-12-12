from ExperimentSuite import ExperimentSuite
from Vectorizer import Vectorizer
import tensorflow as tf
import Preprocessor
import time

DEFAULT_EPOCH = 75
DEFAULT_LAYERS = (512,)
DEFAULT_ACTIVATION = tf.nn.relu
DEFAULT_LOSS = "categorical_hinge"


if __name__ == "__main__":
    # TODO: Make your experiments here
    p = Preprocessor.Preprocessor()
    #p.preprocess()
    es = ExperimentSuite()
    tbCallBack = tf.keras.callbacks.TensorBoard(log_dir='./Graph', histogram_freq=0, write_graph=True, write_images=True)
    train_x = es.train_contents
    train_y = es.train_y
    test_x = es.test_contents
    test_y = es.test_y

   	#min_df = 0.5 and method existance
    ss = time.time()
    vec_1 = Vectorizer(min_df=0.5, max_df=0.97)
    train_x_05_existance = vec_1.fit_transform(train_x, method='existance')
    test_x_05_existance = vec_1.transform(test_x, method='existance')
    print str(time.time() - ss)
    es.train_model(DEFAULT_LAYERS, tbCallBack, train_x_05_existance, train_y, test_x_05_existance, test_y, DEFAULT_LOSS, DEFAULT_ACTIVATION, DEFAULT_EPOCH)
    
    
    #min_df = 0.25 and method existance
    vec_2 = Vectorizer(min_df=0.25, max_df=0.97)
    train_x_025_existance = vec_2.fit_transform(train_x, method='existance')
    test_x_025_existance = vec_2.transform(test_x, method='existance')
    es.train_model(DEFAULT_LAYERS, tbCallBack, train_x_025_existance, train_y, test_x_025_existance, test_y, DEFAULT_LOSS, DEFAULT_ACTIVATION, DEFAULT_EPOCH)
    
    #min_df = 0.1 and method existance
    vec_3 = Vectorizer(min_df=0.1, max_df=0.97)
    train_x_01_existance = vec_3.fit_transform(train_x, method='existance')
    test_x_01_existance = vec_3.transform(test_x, method='existance')
    es.train_model(DEFAULT_LAYERS, tbCallBack, train_x_01_existance, train_y, test_x_01_existance, test_y, DEFAULT_LOSS, DEFAULT_ACTIVATION, DEFAULT_EPOCH)
    
    #min_df = 0.5 and method count
    vec_4 = Vectorizer(min_df=0.5, max_df=0.97)
    train_x_05_existance = vec_4.fit_transform(train_x, method='count')
    test_x_05_existance = vec_4.transform(test_x, method='count')
    es.train_model(DEFAULT_LAYERS, tbCallBack, train_x_05_existance, train_y, test_x_05_existance, test_y, DEFAULT_LOSS, DEFAULT_ACTIVATION, DEFAULT_EPOCH)
    

    
    #min_df = 0.25 and method count
    vec_5 = Vectorizer(min_df=0.25, max_df=0.97)
    train_x_025_count = vec_5.fit_transform(train_x, method='count')
    test_x_025_count = vec_5.transform(test_x, method='count')
    es.train_model(DEFAULT_LAYERS, tbCallBack, train_x_025_count, train_y, test_x_025_count, test_y, DEFAULT_LOSS, DEFAULT_ACTIVATION, DEFAULT_EPOCH)
    

    #min_df = 0.1 and method count
    vec_6 = Vectorizer(min_df=0.1, max_df=0.97)
    train_x_01_count = vec_6.fit_transform(train_x, method='count')
    test_x_01_count = vec_6.transform(test_x, method='count')
    es.train_model(DEFAULT_LAYERS, tbCallBack, train_x_01_count, train_y, test_x_01_count, test_y, DEFAULT_LOSS, DEFAULT_ACTIVATION, DEFAULT_EPOCH)
    

    #min_df = 0.5 and method tf-idf
    vec_7 = Vectorizer(min_df=0.5, max_df=0.97)
    train_x_05_tfidf = vec_7.fit_transform(train_x, method='tf-idf')
    test_x_05_tfidf = vec_7.transform(test_x, method='tf-idf')
    es.train_model(DEFAULT_LAYERS, tbCallBack, train_x_05_tfidf, train_y, test_x_05_tfidf, test_y, DEFAULT_LOSS, DEFAULT_ACTIVATION, DEFAULT_EPOCH)
    

    #min_df = 0.25 and method tf-idf
    vec_8 = Vectorizer(min_df=0.25, max_df=0.97)
    train_x_025_tfidf = vec_8.fit_transform(train_x, method='tf-idf')
    test_x_025_tfidf = vec_8.transform(test_x, method='tf-idf')
    es.train_model(DEFAULT_LAYERS, tbCallBack, train_x_025_tfidf, train_y, test_x_025_tfidf, test_y, DEFAULT_LOSS, DEFAULT_ACTIVATION, DEFAULT_EPOCH)
    

    #min_df = 0.1 and method tf-idf
    vec_9 = Vectorizer(min_df=0.1, max_df=0.97)
    train_x_01_tfidf = vec_9.fit_transform(train_x, method='tf-idf')
    test_x_01_tfidf = vec_9.transform(test_x, method='tf-idf')
    es.train_model(DEFAULT_LAYERS, tbCallBack, train_x_01_tfidf, train_y, test_x_01_tfidf, test_y, DEFAULT_LOSS, DEFAULT_ACTIVATION, DEFAULT_EPOCH)
    

    #best min_df=0.25 and method is count

    #trying layers

    #512
    vec_10 = Vectorizer(min_df=0.25, max_df=0.97)
    train_x_01_count = vec_10.fit_transform(train_x, method='count')
    test_x_01_count = vec_10.transform(test_x, method='count')
    es.train_model((512,), tbCallBack, train_x_01_count, train_y, test_x_01_count, test_y, DEFAULT_LOSS, DEFAULT_ACTIVATION, DEFAULT_EPOCH)

    #512, 256
    vec_11 = Vectorizer(min_df=0.25, max_df=0.97)
    train_x_01_count = vec_11.fit_transform(train_x, method='count')
    test_x_01_count = vec_11.transform(test_x, method='count')
    es.train_model((512, 256), tbCallBack, train_x_01_count, train_y, test_x_01_count, test_y, DEFAULT_LOSS, DEFAULT_ACTIVATION, DEFAULT_EPOCH)

    #512, 256, 128
    vec_12 = Vectorizer(min_df=0.25, max_df=0.97)
    train_x_01_count = vec_12.fit_transform(train_x, method='count')
    test_x_01_count = vec_12.transform(test_x, method='count')
    es.train_model((512, 256, 128), tbCallBack, train_x_01_count, train_y, test_x_01_count, test_y, DEFAULT_LOSS, DEFAULT_ACTIVATION, DEFAULT_EPOCH)

    #best layer configuration is 512, 256

    #trying activations and losses

    #relu and hinge
    vec_13 = Vectorizer(min_df=0.25, max_df=0.97)
    train_x_01_count = vec_13.fit_transform(train_x, method='count')
    test_x_01_count = vec_13.transform(test_x, method='count')
    es.train_model((512, 256), tbCallBack, train_x_01_count, train_y, test_x_01_count, test_y, DEFAULT_LOSS, DEFAULT_ACTIVATION, DEFAULT_EPOCH)
    

    #sigmoid and hinge
    vec_14 = Vectorizer(min_df=0.25, max_df=0.97)
    train_x_01_count = vec_14.fit_transform(train_x, method='count')
    test_x_01_count = vec_14.transform(test_x, method='count')
    es.train_model((512, 256), tbCallBack, train_x_01_count, train_y, test_x_01_count, test_y, DEFAULT_LOSS, tf.nn.sigmoid, DEFAULT_EPOCH)
    

    #tanh and hinge
    vec_15 = Vectorizer(min_df=0.25, max_df=0.97)
    train_x_01_count = vec_15.fit_transform(train_x, method='count')
    test_x_01_count = vec_15.transform(test_x, method='count')
    es.train_model((512, 256), tbCallBack, train_x_01_count, train_y, test_x_01_count, test_y, DEFAULT_LOSS, tf.nn.tanh, DEFAULT_EPOCH)

    

    #relu and crossentropy
    vec_16 = Vectorizer(min_df=0.25, max_df=0.97)
    train_x_01_count = vec_16.fit_transform(train_x, method='count')
    test_x_01_count = vec_16.transform(test_x, method='count')
    es.train_model((512, 256), tbCallBack, train_x_01_count, train_y, test_x_01_count, test_y, 'categorical_crossentropy', DEFAULT_ACTIVATION, DEFAULT_EPOCH)

    #sigmoid and crossentropy
    vec_17 = Vectorizer(min_df=0.25, max_df=0.97)
    train_x_01_count = vec_17.fit_transform(train_x, method='count')
    test_x_01_count = vec_17.transform(test_x, method='count')
    es.train_model((512, 256), tbCallBack, train_x_01_count, train_y, test_x_01_count, test_y, 'categorical_crossentropy', tf.nn.sigmoid, DEFAULT_EPOCH)
    

    #tanh and crossentropy
    vec_18 = Vectorizer(min_df=0.25, max_df=0.97)
    train_x_01_count = vec_18.fit_transform(train_x, method='count')
    test_x_01_count = vec_18.transform(test_x, method='count')
    es.train_model((512, 256), tbCallBack, train_x_01_count, train_y, test_x_01_count, test_y, 'categorical_crossentropy', tf.nn.tanh, DEFAULT_EPOCH)

    #BEST is relu and categorical hinge

    #best with 500 epochs
    
    
    vec_19 = Vectorizer(min_df=0.25, max_df=0.97)
    train_x_01_count = vec_19.fit_transform(train_x, method='count')
    test_x_01_count = vec_19.transform(test_x, method='count')
    es.train_model((512, 256), tbCallBack, train_x_01_count, train_y, test_x_01_count, test_y, DEFAULT_LOSS, DEFAULT_ACTIVATION, 500)


