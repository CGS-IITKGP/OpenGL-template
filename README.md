<div id="top"></div>

<br />
<div align="center">
  <img width="200" alt="image" src="https://github.com/user-attachments/assets/5911a8fb-1232-4c44-8778-a57ea34f7162">
  <h3 align="center">Glint</h3>

  <p align="center">
    <i style="font-size: 0.8em; color: #666;">Originally called ogt (OpenGL Template)</i>
	<br />
    <i>Boilerplate for OpenGL applications</i>
    <br />
  </p>
</div>

<details>
<summary>Table of Contents</summary>

- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Additional documentation](#additional-documentation)
</details>

## Getting Started

_To set up the project, follow the steps below._

### Clone the repository
```sh
git clone https://github.com/CGS-IITKGP/OpenGL-template.git --recurse-submodules
```
**Update submodule using**
```sh
git submodule update --init --recursive
```

### Prerequisites
The following dependencies are required to be installed for the project to function properly:

* **CMake**
	- Linux (Ubuntu/Debian-based)
    
		Install using package managers or from their [CMake GitHub page](https://github.com/Kitware/CMake).

		```shell
		sudo apt update
		sudo apt install cmake
		```
	- macOS

		Install using Homebrew or from their [CMake GitHub page](https://github.com/Kitware/CMake).
		
		```shell
		brew install cmake
		```
	- Windows
    
		Install using the installer or from their [CMake GitHub page](https://github.com/Kitware/CMake).
		1. Download the installer from the [CMake website](https://cmake.org/download/).
    	2. Follow the installation steps.
    	Alternatively, you can install it via winget:
		`winget install cmake`
<p align="right">(<a href="#top">back to top</a>)</p>

### Installation
_The environment has now been set up and configured to properly compile and run the project._

Run `cmake` to compile and run the project

```shell
cmake .
```

The compiled binary is saved in `./build`
To clean the build directory, run

```shell
rm -rf build/
```
<br />

**Note**: The latest version of OpenGL is 4.6 but we are using 4.1 for the sake of macOS compatibility. [Click here to upgrade to the later version](./UPGRADE.md)


<p align="right">(<a href="#top">back to top</a>)</p>

## Additional documentation

  - [License](/LICENSE)
  - [DeepWiki](https://deepwiki.com/CGS-IITKGP/OpenGL-template/)
  - [CONTRIBUTING](./.github/CONTRIBUTING.md)

[![Ask DeepWiki](https://deepwiki.com/badge.svg)](https://deepwiki.com/CGS-IITKGP/OpenGL-template/)

This repo was forked from [dhanvithnayak/OpenGL-template](https://github.com/dhanvithnayak/OpenGL-template)
<p align="right">(<a href="#top">back to top</a>)</p>
