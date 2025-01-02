# Keyword Spotter

## Overview


The data consists of 256 recording sessions each containing multiple recordings from different people and/or background noise. 
216 of 256 data files were used in the model training, and the rest of the data is kept unassigned to any dat set. 
Each recording session contains:

- Audio (16 kHz mono, used as input to the AI model)

The project has the following two classes:

- Up
- Down

Note: If you are using your own data, record it as 16 kHz mono, or edit the project preprocessor to fit your data format.
This Starter Project serves as an example of how you can use audio data to build models. Data to get you started is already added to the project.
You can add more data in the same format to further improve the model.
The output of this project can be deployed to any edge device with a microphone and an MCU/CPU.

## Taking the Project Further

You can take the project further in a number of different ways:

1. You can add additional classes to the existing ones, for example, "left" and "right".

2. Add your own voice to the dataset and see if you can improve the performance for yourself.

3. You can use this project as inspiration to do your own audio project. Simply collect any audio you want and start building.

## Contents

`Data`	- Folder where data is located

- background_noise	- this folder contains all data that's unlabelled. It's intended make the model more robust against random noises and thus lowering false positives
- down	- folder with data for 'down' audio
- up	- folder with data for 'up' audio

`Units` 	- Folder where custom layers and pre-processors can be added

`Models` - Folder where trained models, their predictions and generated Edge code are saved.

## Getting Started

Please visit [developer.imagimob.com](https://developer.imagimob.com), where you can read about Imagimob Studio and go through step-by-step tutorials to get you quickly started.

## Help & Support

If you need support or if you want to know how to deploy the model on to the device, please contact us on the following email: [support@imagimob.com](mailto:support@imagimob.com).

You can also access the Infineon [community forum ](https://community.infineon.com/t5/Imagimob/bd-p/Imagimob/page/1) Imagimob Studio page and ask your questions.
