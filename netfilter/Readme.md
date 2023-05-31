# dummyEthernet:
```shell
cd dummyEther/
make
sudo insmode sample.ko
sudo ifconfig -a
sudo ifconfig dummy0 up
sudo ifconfig dummy0 192.168.7.2
ping 192.168.7.2
dmesg
```
# Netfilter và Socket

- Tạo ra 2 app server và client sử dụng socket. Client sẽ gửi hello đến server. và server in ra hello.
- Netfilter sẽ can thiệp và sửa đổi nội dung của packet từ hello sang goodbye.
- Hiện tại server và client đang chạy trên cùng 1 device nên không áp dụng được netfilter. Nên mọi người cần có 2 thiết bị khác nhau 1 thiết bị chạy server và 1 thiết bị chạy client. Mọi người cần thay đổi địa chỉ của server trong client.c chằng hạn là 192.168.2.1
    ```c
    #define SERVER_IP "127.0.0.1"
    ```
- Mọi người cần build netfilter và insmod vào thiết bị chạy server.