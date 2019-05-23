#!/usr/bin/env python
# coding=utf-8

import tensorflow as tf
#from PIL import Image
#import numpy as np
from tensorflow.examples.tutorials.mnist import input_data

data = input_data.read_data_sets("data/", one_hot = True)
all_x = data.train.images
all_y = data.train.labels
test_x = data.test.images
test_y = data.test.labels


with tf.Session() as sess:
    x = tf.placeholder(shape = [None, 784], dtype = tf.float32)
    y = tf.placeholder(shape = [None, 10], dtype = tf.float32)
    W = tf.Variable(tf.zeros(shape = [784, 10]))
    b = tf.Variable(tf.zeros(shape = [10]))
    output = tf.nn.softmax(tf.matmul(x, W) + b)
    cross_entropy = tf.reduce_mean(-tf.reduce_sum(y * tf.log(output)))
    train_step = tf.train.GradientDescentOptimizer(0.01).minimize(cross_entropy)
    sess.run(tf.global_variables_initializer())
    
    equal_tensor = tf.cast(tf.equal(tf.argmax(y, 1), tf.argmax(output, 1)), tf.float32)
    accuracy = tf.reduce_mean(equal_tensor)

    for i in range(2000):
        tx, ty = data.train.next_batch(100)
        sess.run(train_step, feed_dict = {x : tx, y : ty})
        if i % 50 == 0:
            acc = sess.run(accuracy, feed_dict = {x : test_x, y : test_y})
            print("accuracy : %lf" % acc)
