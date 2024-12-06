# Use an NVIDIA base image with Vulkan support
FROM nvidia/opengl:1.2-glvnd-runtime-ubuntu20.04

# Install dependencies for Unreal Engine
RUN apt-get update && apt-get install -y \
    libx11-6 \
    libx11-xcb1 \
    libxcb1 \
    libxrandr2 \
    libxinerama1 \
    libxcursor1 \
    libxi6 \
    libgl1-mesa-glx \
    libvulkan1 \
    && rm -rf /var/lib/apt/lists/*

# Copy the packaged Unreal Engine app to the container
COPY ./Builds/Linux /app

# Set the working directory
WORKDIR /app

# Expose any required ports (optional)
EXPOSE 7777

# Command to run your Unreal Engine app
CMD [".TimeParadox"]