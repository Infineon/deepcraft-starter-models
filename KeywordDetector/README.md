# Keyword Detector

## Overview

This machine learning project contains everything to get started with keyword detection. Bundled with the project is a trained model, the Google Speech commands dataset, and the guide how to download and prepare the dataset.

## Data

The original dataset can be downloaded from [here](http://download.tensorflow.org/data/speech_commands_v0.02.tar.gz).
The dataset differs from the original dataset in that the single wave files are concatenated to longer time series by stitching them together with 0.1 seconds of silence in between 
to prevent that multiple words are in one input time window of the model. For the transformation, you need to modify the paths in the Python script (locatied at Tools/prepare_dataset.py).

You can add more data by recording with your preferred recorder app of the OS, Deepcraft Studio's [Graph UX](https://developer.imagimob.com/data-preparation/data-collection/collect-data-using-graph-ux) with either your Computer mic or an MCU with [Imagimob Streaming protocoll](https://github.com/Infineon/mtb-example-imagimob-streaming-protocol).


## Contents

`Data`	- Folder where data is located

- Each track has its own folder. A track is a 15-20 minutes long audio stream.

- Each folder should contain the raw audio file "data.wav" and the label file "label.label". Both are created by the script "prepare_dataset.py"

`Units` 	- Folder where custom layers and pre-processors can be added

`Models` - Folder where trained models, their predictions and generated Edge code are saved.


## How to train models

Install Imagimob Studio

Open KeywordDetector.improj with Studio

Open the "Training" Tab and generate a new model list. Use the GUI config for network size, etc.

Click "Start new Training Job" and submit the Job, Log-in to Imagimob Account

After Training is finished, download model(s)