# Trạm Băng Tải, Dập và Gia Nhiệt Tự Động

## Tổng quan dự án

Đây là một dự án hệ thống nhúng được phát triển với PlatformIO để điều khiển một trạm làm việc tự động nhỏ.
Hệ thống quản lý một băng tải, một cơ chế dập và một bộ phận gia nhiệt để thực hiện một **quy trình sản xuất tuần tự**.

Phần cứng mục tiêu là vi điều khiển dựa trên ATmega328, thường được tìm thấy trên các bo mạch như Arduino Uno hoặc Nano.

## Các thành phần cốt lõi

Hệ thống điều khiển các phần cứng sau:

1.  **Bộ gia nhiệt (`heater`)**
    *   Bộ phận gia nhiệt **luôn BẬT** trong suốt quá trình vận hành máy.
2.  **Động cơ băng tải (`motorConveyor`)**
    *   Di chuyển sản phẩm dọc theo băng tải.
3.  **Động cơ dập (`motorPunch`)**
    *   Kích hoạt cơ chế dập hoặc ép.
4.  **Công tắc hành trình**
    *   Bốn công tắc hành trình phát hiện vị trí của cơ chế dập và băng tải:
        *   Vị trí Băng tải VÀO
        *   Vị trí Băng tải RA
        *   Vị trí Dập XUỐNG
        *   Vị trí Dập LÊN
5.  **Nút khởi động**
    *   Một nút nhấn để bắt đầu chu trình hoàn chỉnh.

## Quy trình làm việc

Trình tự hoạt động, được triển khai trong lớp `Process`, như sau:

1.  Hệ thống ở trạng thái chờ cho đến khi **Nút khởi động** được nhấn.
2.  **Bộ gia nhiệt BẬT và duy trì trạng thái BẬT.**
3.  **Động cơ băng tải** chạy về phía trước cho đến khi **công tắc hành trình VÀO** được kích hoạt (sản phẩm di chuyển vào vị trí).
4.  **Động cơ dập** di chuyển **XUỐNG** cho đến khi **công tắc hành trình XUỐNG** được kích hoạt.
5.  Hệ thống **chờ cho đến khi bộ gia nhiệt đạt đủ nhiệt độ** (hoặc một độ trễ gia nhiệt cố định).
6.  **Động cơ dập** di chuyển một phần **LÊN** cho đến khi **công tắc hành trình LÊN** được kích hoạt.
7.  **Động cơ băng tải** chạy lại để di chuyển sản phẩm RA cho đến khi **công tắc hành trình RA** được kích hoạt.
8.  Hệ thống trở về trạng thái chờ, chờ chu trình tiếp theo.
9.  **Bộ gia nhiệt vẫn BẬT** cho các chu trình tiếp theo.

Logic này đảm bảo bộ gia nhiệt luôn hoạt động và cơ chế dập/băng tải hoạt động theo trình tự chính xác.

---

## Phần mềm & Cấu trúc

*   **Framework:** [Arduino](https://www.arduino.cc/)
*   **Hệ thống xây dựng:** [PlatformIO](https://platformio.org/)
*   **Ngôn ngữ:** C++
*   **Các tệp chính:**
    *   `src/main.cpp`: Điểm vào. Khởi tạo tất cả các đối tượng và bắt đầu vòng lặp chính.
    *   `src/process.cpp`: Chứa logic quy trình làm việc cốt lõi được mô tả ở trên.
    *   `src/motor.cpp`: Lớp điều khiển động cơ (bật/tắt).
    *   `src/heater.cpp`: Lớp điều khiển bộ gia nhiệt (bật/tắt).
    *   `src/pinConfig.h`: Định nghĩa ánh xạ chân cho tất cả phần cứng.

---

## Cách xây dựng

1.  Cài đặt [Visual Studio Code](https://code.visualstudio.com/) và tiện ích mở rộng [PlatformIO IDE](https://platformio.org/platformio-ide).
2.  Clone kho lưu trữ này.
3.  Mở thư mục dự án trong VS Code.
4.  Để xây dựng dự án, chạy lệnh: `platformio run`
5.  Để xây dựng và tải lên bo mạch đã kết nối, chạy: `platformio run --target upload`

## Các vấn đề đã biết

*   Tệp `main.cpp` hiện không đồng bộ với lớp `Process`. Nó không tạo và truyền đối tượng `Heater` cần thiết trong quá trình khởi tạo đối tượng `process`, điều này sẽ gây ra **lỗi biên dịch**. Điều này cần được khắc phục để dự án xây dựng thành công.