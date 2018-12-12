from ExperimentSuiteBonus import ExperimentSuite
from Vectorizer import Vectorizer
import tensorflow as tf
#import scipy.io as sio

DEFAULT_EPOCH = 75
DEFAULT_LAYERS = (512,)
DEFAULT_ACTIVATION = tf.nn.relu
DEFAULT_LOSS = "categorical_hinge"


if __name__ == "__main__":
	es = ExperimentSuite()
	tbCallBack = tf.keras.callbacks.TensorBoard(log_dir='./Graph', histogram_freq=0, write_graph=True, write_images=True)
	train_x = es.train_contents
	train_y = es.train_y
	test_x = es.test_contents
	test_y = es.test_y


	vec = Vectorizer(min_df=0.25, max_df=0.97)
	train_x_01_count = vec.fit_transform(train_x, method='count')
	test_x_01_count = vec.transform(test_x, method='count')
	es.train_model((512, 256), tbCallBack, train_x_01_count, train_y, test_x_01_count, test_y, DEFAULT_LOSS, DEFAULT_ACTIVATION, 500, 0.5, True)
	es.train_model((512, 256, 128), tbCallBack, train_x_01_count, train_y, test_x_01_count, test_y, DEFAULT_LOSS, DEFAULT_ACTIVATION, 500, 0.5, True)
	es.train_model((512, 256, 256, 128), tbCallBack, train_x_01_count, train_y, test_x_01_count, test_y, DEFAULT_LOSS, DEFAULT_ACTIVATION, 500, 0.5, True)
	es.train_model((512, 256, 128, 64, 32), tbCallBack, train_x_01_count, train_y, test_x_01_count, test_y, DEFAULT_LOSS, DEFAULT_ACTIVATION, 500, 0.5, True)
	es.train_model((512, 256), tbCallBack, train_x_01_count, train_y, test_x_01_count, test_y, DEFAULT_LOSS, DEFAULT_ACTIVATION, 600, 0.25, True)
	es.train_model((512, 256), tbCallBack, train_x_01_count, train_y, test_x_01_count, test_y, DEFAULT_LOSS, tf.nn.leaky_relu, 500, 0.5, True)
	es.train_model((512, 256, 128), tbCallBack, train_x_01_count, train_y, test_x_01_count, test_y, DEFAULT_LOSS, tf.nn.leaky_relu, 500, 0.5, True)
	es.train_model((512, 256, 256, 128), tbCallBack, train_x_01_count, train_y, test_x_01_count, test_y, DEFAULT_LOSS, tf.nn.leaky_relu, 500, 0.5, True)
	es.train_model((512, 256, 128, 64, 32), tbCallBack, train_x_01_count, train_y, test_x_01_count, test_y, DEFAULT_LOSS, tf.nn.leaky_relu, 500, 0.5, True)
	es.train_model((512, 256), tbCallBack, train_x_01_count, train_y, test_x_01_count, test_y, DEFAULT_LOSS, DEFAULT_ACTIVATION, 600, 0.25, True)

