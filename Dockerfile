# Use the official Ubuntu base image
FROM ubuntu:20.04

# Set environment variables to avoid user interaction during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Update the package list and install necessary packages
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    cmake \
    qt5-default \
    qt5-qmake \
    libqt5widgets5 \
    qtbase5-dev \
    qtdeclarative5-dev \
    git \
    && apt-get clean

# Create a directory for the application
WORKDIR /app

# Copy the project files to the working directory
COPY . /app

# Build the Qt project
RUN qmake && make

# Set the entry point for the container
CMD ["./YourQtAppExecutable"]
