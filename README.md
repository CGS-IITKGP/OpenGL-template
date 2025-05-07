<div id="top"></div>

<br />
<div align="center">
  <img width="200" alt="image" src="https://github.com/user-attachments/assets/5911a8fb-1232-4c44-8778-a57ea34f7162">
  <h3 align="center">OpenGL Template</h3>

  <p align="center">
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
git clone https://github.com/CGS-IITKGP/OpenGL-template.git
```

### Prerequisites
The following dependencies are required to be installed for the project to function properly:
* **GLFW** <br />
  You can install this from any package manager, if you use one (e.g., `apt` for Debian-based systems, `brew` or `choco`)
  ```sh
  sudo apt install libglfw3 libglfw3-dev

  # Uncomment this if you use Wayland
  # sudo apt install libglfw3-wayland
  ```
  Otherwise, install binaries from their [download page](https://www.glfw.org/download.html) <br />
  If you are feeling especially adventurous, you could build from source <br />
* **glad** <br />
  Go to the [glad web service](http://glad.dav1d.de), set language as C++, OpenGL version to 4.6 and profile to Core. Make sure `generate loader` option is selected.
  Click Generate and copy the `glad` and `KHR` folders to your includes location

  Relevant learnopengl page for GLFW and glad: [link](https://learnopengl.com/Getting-started/Creating-a-window)
* **glm** <br />
  Install using package managers or from their [downloads page](https://glm.g-truc.net/0.9.8/index.html)
  ```sh
  sudo apt install libglm-dev
  ```
  Relevant learnopengl page: [link](https://learnopengl.com/Getting-started/Transformations) look for the In Practice section
* **assimp** <br />
  Install using package managers or from their [Github page](https://github.com/assimp/assimp/blob/master/Build.md)
  ```sh
  sudo apt install lilbassimp5 libassimp-dev
  ```
  Or, build from source
* **Make** <br />
  Unix-like systems can get `make` through package managers
  ```sh
  sudo apt install make
  ```
  For Windows, you can get [Make for Windows](https://gnuwin32.sourceforge.net/packages/make.htm), use [Chocolatey](https://chocolatey.org/install) to install `make` or use WSL2
  ```sh
  choco install make
  ```
<p align="right">(<a href="#top">back to top</a>)</p>

### Installation

_The environment has now been set up and configured to properly compile and run the project._

Run `make` to compile and run the project
```sh
make
```
The compiled binary is saved in `./build`

To clean the build directory, run
```sh
make clean
```

<p align="right">(<a href="#top">back to top</a>)</p>

## Additional documentation

  - [License](/LICENSE)
  - [DeepWiki](https://deepwiki.com/dhanvithnayak/OpenGL-template)
  - [CONTRIBUTING](./.github/CONTRIBUTING.md)

<p align="right">(<a href="#top">back to top</a>)</p>
