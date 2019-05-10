#!/usr/bin/env python
# coding=utf-8

import tensorflow as tf
#from PIL import image
from tensorflow.examples.tutorials.mnist import input_data

data = input_data.read_data_sets("data/", one_hot = True)
'''


all_x = data.train.images
all_y = data.train.lables
test_x = data.test.images
test_y = data.test.lables

with tf.Session() as sess:
    x = tf.plaseholder(shape = [None, 784])
    y = tf.plaseholder(shape = [None,10])
    #y_labels = tf.argmax(output, 1)
    #
    W = tf.Variable(tf.zeros(shape = [784,10]))
    b = tf.Variable(tf.zeros(shape = [10]))
    output = tf.nn.softmax(tf.matmul(x,W) + b)
    output_label = tf.argmax(output, 1)
    #交叉熵
    cross_entropy = tf.reduse_mean(-tf.reduse_sum(y * tf.log(output)))
    train_step = tf.train.GradientDescentOptimizer(0.01).minimize(cross_entropy)
    sess.run(tf.global_variables_initalizer())

    #强制类型转换
    euqal_tensor = tf.cast(tf.equal(tf.argmax(y,1), tf.argmax(output,1)), tf.float32)
    accuracy = tf.reduce_mean(euqal_tensor)

    for i in range(2000):
        tx, ty = data.train.next_batch(50)
        sess.run(train_step,feed_dict = {x : tx,y : ty})
        if i % 50 == 0:
            acc = sess.run(accuracy, feed_dict = {x : test_x, y : test_y})
            print ("accuracy : %lf" % acc)

    #eval_labels = sess.run(output_label,feed_dict = {x : test_x})
    #y_labels  
    #
    #for image, label, eval_label  in zip(test_x, test_y,eval_labels)
    #    image_data = np.reshape(image,)
   #    print (eval_label)
'''
