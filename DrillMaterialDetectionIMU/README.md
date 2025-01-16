# Drill Material Detection w/ IMU

## Overview

This is a starter model which is capable of classifying the material a power drill is drilling into based on the IMU (6 axis accelerometer and gyroscope) data and is imagined to be incorporated into smart power tools. 
It is developed as a proof of concept and is not fully optimized, achieving around a 90% plastic/wood accuracy but only about 50% for air/none.
However the air/none accuracy can easily be disregarded since other simple solutions can differentiate if the drill is active or not. 
Furthermore it only diffirentiates between wood, plastic and air. 

## Collection of Data
The data was collected from the built in accelerometer and gyroscope on the AI-Eval kit (CY8CKIT-062S2-AI) taped to the left top side of a drill, streamed directly into DEEPCRAFT Studio at 50Hz. Apart from drilling into air, wood and plastic the drill was moved around in order to create an invariance.
There are additional labels for the moment of removing the drill from the material, called wood_out and plastic_out.

## Adding More Data
In order to add more data and/or another material (such as metal) you simply need to attach an AI-eval kit, purchasable here: https://www.infineon.com/cms/en/product/evaluation-boards/cy8ckit-062s2-ai/,  to a drill and stream the IMU data of drilling into DEEPCRAFT Studio and then label it appropriately. 
It is recommended to have a minimum of 100 seconds per label, preferrably more.

## Steps to Production
The recommended path to production for this starter model is to identify which materials you want to differentiate from and removing the existing data that doesn't match. 
Then perform data collection as outlined above. 
Then the preprocessing and model parameters should be optimized and refined, with size considerations based on your final deployment location