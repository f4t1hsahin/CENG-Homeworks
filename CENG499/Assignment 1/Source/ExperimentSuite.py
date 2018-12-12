from OneHotEncoder import OneHotEncoder
import os
from sklearn.metrics import confusion_matrix
import tensorflow as tf
import functools
import numpy as np
tf.logging.set_verbosity(tf.logging.ERROR)

top3_acc = functools.partial(tf.keras.metrics.top_k_categorical_accuracy, k=3)

top3_acc.__name__ = 'top3_acc'


top2_acc = functools.partial(tf.keras.metrics.top_k_categorical_accuracy, k=2)

top2_acc.__name__ = 'top2_acc'

metrics = ['categorical_accuracy', top2_acc, top3_acc]

class ExperimentSuite:
    def __init__(self, dataset_directory = "ProcessedDataset", train_directory = "TrainDataset", test_directory = "TestDataset"):
        self.dataset_directory = dataset_directory
        self.train_directory = train_directory
        self.test_directory = test_directory

        self.train_contents = []
        self.train_labels = []
        self.test_contents = []
        self.test_labels = []
        self.read_data()

        self.enc = OneHotEncoder()
        self.enc.fit(self.train_labels)
        self.train_y = self.enc.transform(self.train_labels)
        self.test_y = self.enc.transform(self.test_labels)

    def train_model(self,layers, tbCallBack, train_x, train_y, test_x, test_y, loss, activation, epoch):
        """Creates a model, adds each layer in layers with given activation function. Compile the model with
        given loss. Fit the model with given number of epoch.

        :param layers: tuple of integers
        :param tbCallBack: tensorboard log callback
        :param train_x: numpy array for train data
        :param train_y: numpy array for train label
        :param test_x: numpy array for test data
        :param test_y: numpy array for test label
        :param loss: loss function: categorical_crossentropy or categorical_hinge
        :param activation: activation function for hidden layers: sigmoid, relu or tanh
        :param epoch: epoch for model to train
        :return: evaluate result for test set
        """
        model = tf.keras.models.Sequential()

        # TODO: Add layers for each layer in layers
        # TODO: Add output layer with softmax activation function
        # TODO: Compile the model with given loss and metrics
        # TODO: Fit the model with given train data, epoch and tensorboard callback
        y_dim = self.train_y.shape
        y_dim = y_dim[1]
        x_dim = train_x.shape[1]
        model.add(tf.keras.layers.Dense(layers[0], activation=activation, input_dim=x_dim))
        for layer in layers[1:]:
            model.add(tf.keras.layers.Dense(layer, activation=activation))
        model.add(tf.keras.layers.Dense(y_dim, activation='softmax'))

        model.compile(loss=loss, optimizer='adam', metrics=metrics)

        hist = model.fit(train_x, train_y, epochs=epoch, callbacks=[tbCallBack], verbose=0)

        #save_name = str(layers) + '_' + str(loss) + '_' + str(activation.__name__)+ '_' + str(epoch) + '_loss_acc'

        #sio.savemat(save_name, hist.history)

        #remove for submission
        

        evaluation = model.evaluate(test_x, test_y, verbose=0)
        print "Activation function:", activation.__name__
        print "Loss function:", loss
        print "Layers:",layers
        print "Test set evaluation:",zip(model.metrics_names, evaluation)
        Y_pred = model.predict(test_x)
        y_pred = np.argmax(Y_pred, axis=1)
        print 'Confusion Matrix'
        print self.enc.get_feature_names()
        print(confusion_matrix(test_y.argmax(axis=1), y_pred))
        print "\n"

        #save_name2 = str(layers) + '_' + str(loss) + '_' + str(activation.__name__)+ '_' + str(epoch) + '_conf_mat'
        #dd = {}
        #dd['confusion_matrix'] = confusion_matrix(test_y.argmax(axis=1), y_pred)
        #sio.savemat(save_name2, dd)
        return evaluation

    def read_data(self):
        for root, dirs, files in os.walk(self.dataset_directory + "/" + self.train_directory):
            for file in files:
                self.train_labels.append(os.path.basename(root))
                with open(root + "/" + file, "r") as i:
                    self.train_contents.append(i.read())

        for root, dirs, files in os.walk(self.dataset_directory + "/" + self.test_directory):
            for file in files:
                self.test_labels.append(os.path.basename(root))
                with open(root + "/" + file, "r") as i:
                    self.test_contents.append(i.read())


# cizdirmek icin matplotlib
# # summarize history for accuracy
# plt.plot(history.history['acc'])
# plt.plot(history.history['val_acc'])
# plt.title('model accuracy')
# plt.ylabel('accuracy')
# plt.xlabel('epoch')
# plt.legend(['train', 'test'], loc='upper left')
# plt.show()
# # summarize history for loss
# plt.plot(history.history['loss'])
# plt.plot(history.history['val_loss'])
# plt.title('model loss')
# plt.ylabel('loss')
# plt.xlabel('epoch')
# plt.legend(['train', 'test'], loc='upper left')
# plt.show()