# Use official GCC image
FROM gcc:latest

# Set working directory
WORKDIR /app

# Copy source and headers
COPY include/ include/
COPY src/ src/
COPY CMakeLists.txt .

# Install dependencies: wget, make, latest CMake, and Telnet client
RUN apt-get update && \
    apt-get install -y wget make telnet && \
    wget https://github.com/Kitware/CMake/releases/download/v3.26.4/cmake-3.26.4-linux-x86_64.sh && \
    chmod +x cmake-3.26.4-linux-x86_64.sh && \
    mkdir -p /opt/cmake && \
    ./cmake-3.26.4-linux-x86_64.sh --prefix=/opt/cmake --skip-license && \
    ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake && \
    rm cmake-3.26.4-linux-x86_64.sh

# Build the project
RUN cmake . && make

# Expose port for TCP server
EXPOSE 5678

# Create a script to run the server in the background and then open bash
RUN echo '#!/bin/bash\n\
    ./SimpleTCPKeyValueServer 5678 &\n\
    exec /bin/bash' > /start.sh && \
    chmod +x /start.sh

# Set the entrypoint to the script
ENTRYPOINT ["/start.sh"]