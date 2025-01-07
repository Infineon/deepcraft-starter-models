# DEEPCRAFT™ Starter Models
This repository contains DEEPCRAFT™ Starter Models - deep learning based projects for various use-cases designed as starting points for building custom applications. These projects include data and project files ready to use with DEEPCRAFT™ Studio.

This repository is automatically pulled and content is generated in DEEPCRAFT™ Studio. For the best experience, access these models through DEEPCRAFT™ Studio.

## Usage
These projects are designed to be used through DEEPCRAFT™ Studio (https://www.imagimob.com/studio) and should be accessed through that platform.

## Contribution
All users are welcome to submit new models/projects, subject to the Infineon DEEPCRAFT™ Starter Model review process.

## Submission Process
To submit a project, create a pull request with your data and DEEPCRAFT™ Studio project file (.improj). All project submissions must include a README file with the following information:
* Use-case description
* Sensor settings specifications
* Guidelines for collecting and expanding the dataset
* Recommended path to production, including steps to make the model production-ready

To create your pull request, download and unpack the [Create PR tool](https://api.imagimob.com/v1/Data/Object/create_pr.zip), then run:

```bash
python .\create_pr.py --path <project-path>
```

where `<project-path>` is the root path of the starter model project. For more information review the tools' `README.md` file.

***NOTE:*** The pipline will automatically generate the pre-processing, model predictions and train some models based on the default best model selection from DEEPCRAFT™ Studio. If you would not like to have this, then please specify in the pull request if that should not be what should be published.
