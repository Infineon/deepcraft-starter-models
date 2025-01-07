# DEEPCRAFT™ Starter Models
This repository contains DEEPCRAFT™ Starter Models - deep learning based projects for various use-cases designed as starting points for building custom applications. These projects have data and a project file that is ready to be used with DEEPCRAFT™ Studio.

This repository is automatically pulled and content is generated in DEEPCRAFT™ Studio. For the best experience, access these models through DEEPCRAFT™ Studio.

## Usage
These projects are designed to be used through DEEPCRAFT™ Studio (https://www.imagimob.com/studio) and should be accessed through that platform.

## Contribution
All users are welcome to submit new models/projects, subject to the Infineon DEEPCRAFT™ Starter Model review process.

## Submission Process
To submit a project, create a pull request with your data and DEEPCRAFT™ Studio project file (.improj) using the automation tool provided below.

All project submissions must include a README file with the following information:
* Use-case description
* Sensor settings specifications
* Guidelines for collecting and expanding the dataset
* Recommended path to production, including steps to make the model production-ready

Once the project is ready, you can download and unpack the [Create PR tool](https://api.imagimob.com/v1/Data/Object/create_pr.zip), then run the following command from within the unpacked directory:

```bash
python .\create_pr.py --path <project-path>
```

where `<project-path>` is the root path of the starter model project. For more information review the tools' `README.md` file.

Please be aware that you will need a GitHub Account. When you run the tool using the command shown above it will authenticate using your GitHub account, fork this repository and prepare the pull request. Once ready, it will open the pull request in a window in your browser. Please add the relevant detail requested to complete your pull request which will aid in the review process and then submit.

***NOTE:*** The pipline will automatically generate the pre-processing, model predictions and train some models based on the default best model selection from DEEPCRAFT™ Studio. If you would not like to have this, then please specify in the pull request if that should not be what should be published.
