FROM 833988750864.dkr.ecr.us-east-2.amazonaws.com/ubuntu_builder:0.0.5 as base
ENV TEST_CLICKUP=TRUE

COPY . dir
RUN cd /dir && mkdir build && cd build && \
    cmake .. \
    -DCMAKE_BUILD_TYPE=Debug \
    -DCPP_STANDARD=17 \
    -DCMAKE_CXX_COMPILER=clang++  && \
    make

EXPOSE 4572
EXPOSE 4566

FROM base as test
RUN [ "sh", "-c", "/dir/build/test/clickup_test" ]
