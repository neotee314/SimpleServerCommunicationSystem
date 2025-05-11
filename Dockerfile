# استفاده از تصویر پایه gcc
FROM gcc:latest

# تنظیم دایرکتوری کاری داخل کانتینر
WORKDIR /app

# فایل‌ها را کپی کن
COPY include/ include/
COPY src/ src/
COPY CMakeLists.txt .

# نصب نسخه جدید CMake
RUN apt-get update && apt-get install -y wget \
    && wget https://github.com/Kitware/CMake/releases/download/v3.26.4/cmake-3.26.4-linux-x86_64.sh \
    && chmod +x cmake-3.26.4-linux-x86_64.sh \
    && mkdir -p /opt/cmake \
    && ./cmake-3.26.4-linux-x86_64.sh --prefix=/opt/cmake --skip-license \
    && ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake






# نصب make
RUN apt-get install -y make

# ساخت پروژه با استفاده از CMake و Make
RUN cmake . && make

# پورت را برای ارتباط باز کن
EXPOSE 5678

# اجرای برنامه پس از ساخت
CMD ["./SimpleTCPKeyValueServer"]
