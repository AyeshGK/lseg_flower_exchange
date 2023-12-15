# Flower Exchange Project

## Overview

This repository contains the source code for the Flower Exchange project, an assignment project developed for LSEG (London Stock Exchange Group). The project is designed to facilitate the exchange of flowers, providing a platform for buyers and sellers to connect and conduct transactions.

## Project Structure

The project is organized into the following directories:

- **src:** Contains the C++ source code for the Flower Exchange project.
  - **dao:** Data Access Object components.
  - **service:** Service components for business logic.
  - **model:** Data models representing entities in the Flower Exchange system.
  - **factory:** Factory components for object creation.
  - **common:** Common utility functions and classes.

- **include:** Header files for the C++ source code.

- **build:** Directory where the compiled object files and the final executable are stored.

- **data:** Placeholder directory for storing data related to the Flower Exchange system.
  - **orders:** Directory for CSV files containing order data.
  - **results:** Directory for storing result files.

## Prerequisites

Before building and running the project, make sure you have the following installed on your system:

- **C++ Compiler:** Ensure that a C++ compiler is installed on your system. You may use a specific version; for example, g++ version 9.

- **Make:** The project utilizes a Makefile for compilation. Make sure you have the `make` utility installed.

## Data Files

1. Add CSV files containing order data to the `data/orders` directory.

2. Update file paths in `src/main.cpp` to point to the correct data files.

## Build and Run Instructions

1. Open a terminal and navigate to the project directory.

2. Run the following command to build the project:
   ```bash
   make
   ```

3. To run the Flower Exchange application, use the following command:
   ```bash
   make run
   ```

4. To clean up the build artifacts, run:
   ```bash
   make clean
   ```

## Developers

The Flower Exchange project was developed by:

### Ayesh Vininda

- **LinkedIn:** [Ayesh Vininda](https://www.linkedin.com/in/ayesh-vininda-1998gk)
- **GitHub:** [AyeshVininda](https://github.com/AyeshGK)
- **Email:** ayeshgk@gmail.com

### Prasad Darshana

- **LinkedIn:** [Prasad Darshana](https://www.linkedin.com/in/prasaddarshana/)
- **GitHub:** [PrasadDarshana](https://github.com/PrasadDSandaruwan)
- **Email:** prasaddarshana1999@gmail.com

## Additional Information

- The Flower Exchange project is structured to enhance code organization, with separate directories for different components.

- The Makefile simplifies the build process by specifying compiler flags, source file locations, and build targets.

- The project is an assignment project for LSEG, and any specific requirements or guidelines should be referenced in the project documentation.

Feel free to explore and customize the codebase according to project requirements. If you have any questions or encounter issues, refer to the documentation or seek assistance from the project contributors.

**Note:** Ensure that the necessary permissions are granted to execute the `make` commands and the final executable. If needed, use the `chmod` command to adjust permissions.