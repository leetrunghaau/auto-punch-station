# Trạm Dập – Gia Nhiệt Tự Động

## 🚀 Tổng quan dự án

Đây là một dự án hệ thống nhúng được phát triển bằng PlatformIO, nhằm điều khiển một trạm làm việc tự động thu nhỏ. Hệ thống này quản lý một băng tải, một cơ chế dập và một bộ phận gia nhiệt để thực hiện một quy trình sản xuất tuần tự.

Phần cứng mục tiêu là vi điều khiển dựa trên ATmega328, thường được tìm thấy trên các bo mạch như Arduino Uno hoặc Nano.

## ✨ Tính năng chính

*   **Điều khiển tuần tự:** Thực hiện quy trình sản xuất theo các bước được định nghĩa rõ ràng.
*   **Điều khiển động cơ hai chiều:** Hỗ trợ điều khiển động cơ băng tải và động cơ dập theo cả hai chiều (tiến/lùi, lên/xuống).
*   **Gia nhiệt tự động:** Bộ gia nhiệt hoạt động liên tục trong suốt chu trình.
*   **Phát hiện vị trí chính xác:** Sử dụng công tắc hành trình để xác định vị trí của băng tải và cơ chế dập.
*   **Khởi động bằng nút nhấn:** Bắt đầu chu trình sản xuất thông qua một nút nhấn.
*   **Xử lý nhiễu đầu vào (Debouncing):** Đảm bảo các tín hiệu từ nút nhấn và công tắc hành trình được đọc chính xác, loại bỏ nhiễu điện.
*   **Cấu hình tập trung:** Các tham số quan trọng như thời gian chờ gia nhiệt và thời gian timeout của động cơ được định nghĩa tập trung để dễ dàng quản lý.
*   **Xử lý lỗi an toàn (Timeout):** Tự động dừng động cơ và chuyển sang trạng thái lỗi nếu công tắc hành trình không được kích hoạt trong một khoảng thời gian nhất định, ngăn ngừa hư hỏng cơ khí.

## 🛠️ Thành phần phần cứng

Hệ thống điều khiển các phần cứng sau:

1.  **Bộ gia nhiệt (`Heater`):** Bộ phận gia nhiệt luôn BẬT trong suốt quá trình vận hành máy.
2.  **Động cơ băng tải (`MotorConveyor`):** Di chuyển sản phẩm dọc theo băng tải (hỗ trợ tiến/lùi).
3.  **Động cơ dập (`MotorPunch`):** Kích hoạt cơ chế dập hoặc ép (hỗ trợ lên/xuống).
4.  **Công tắc hành trình:** Bốn công tắc hành trình phát hiện vị trí:
    *   Vị trí Băng tải VÀO
    *   Vị trí Băng tải RA
    *   Vị trí Dập XUỐNG
    *   Vị trí Dập LÊN
5.  **Nút khởi động:** Một nút nhấn để bắt đầu chu trình hoàn chỉnh.

## ⚙️ Quy trình làm việc

Trình tự hoạt động, được triển khai trong lớp `Process`, như sau:

1.  Hệ thống ở trạng thái chờ cho đến khi **Nút khởi động** được nhấn.
2.  **Bộ gia nhiệt BẬT và duy trì trạng thái BẬT.**
3.  **Động cơ băng tải** chạy về phía trước cho đến khi **công tắc hành trình VÀO** được kích hoạt (sản phẩm di chuyển vào vị trí).
4.  **Động cơ dập** di chuyển **XUỐNG** cho đến khi **công tắc hành trình XUỐNG** được kích hoạt.
5.  Hệ thống **chờ cho đến khi bộ gia nhiệt đạt đủ nhiệt độ** (hoặc một độ trễ gia nhiệt cố định).
6.  **Động cơ dập** di chuyển **LÊN** cho đến khi **công tắc hành trình LÊN** được kích hoạt.
7.  **Động cơ băng tải** chạy lại để di chuyển sản phẩm RA cho đến khi **công tắc hành trình RA** được kích hoạt.
8.  Hệ thống trở về trạng thái chờ, chờ chu trình tiếp theo.
9.  **Bộ gia nhiệt vẫn BẬT** cho các chu trình tiếp theo.

Logic này đảm bảo bộ gia nhiệt luôn hoạt động và cơ chế dập/băng tải hoạt động theo trình tự chính xác và an toàn.

## 💻 Cấu trúc phần mềm

*   **Framework:** [Arduino](https://www.arduino.cc/)
*   **Hệ thống xây dựng:** [PlatformIO](https://platformio.org/)
*   **Ngôn ngữ:** C++
*   **Các tệp chính:**
    *   `src/main.cpp`: Điểm vào của chương trình. Khởi tạo tất cả các đối tượng và chứa vòng lặp chính.
    *   `src/process.h` / `src/process.cpp`: Chứa logic quy trình làm việc cốt lõi và máy trạng thái.
    *   `src/motor.h` / `src/motor.cpp`: Định nghĩa và triển khai lớp điều khiển động cơ (hai chiều).
    *   `src/heater.h` / `src/heater.cpp`: Định nghĩa và triển khai lớp điều khiển bộ gia nhiệt.
    *   `src/pinConfig.h`: Định nghĩa ánh xạ chân phần cứng và các hằng số cấu hình hệ thống.
    *   `src/utils.h` / `src/utils.cpp`: Chứa các lớp và hàm tiện ích, bao gồm lớp `Button` để xử lý nhiễu đầu vào.

## 🚀 Hướng dẫn xây dựng và tải lên

Để xây dựng và tải chương trình lên bo mạch vi điều khiển, bạn cần cài đặt PlatformIO IDE.

1.  Cài đặt [Visual Studio Code](https://code.visualstudio.com/) và tiện ích mở rộng [PlatformIO IDE](https://platformio.org/platformio-ide).
2.  Clone kho lưu trữ này:
    ```bash
    git clone https://github.com/your-username/your-repo-name.git
    cd your-repo-name
    ```
3.  Mở thư mục dự án trong VS Code.
4.  Để xây dựng dự án, chạy lệnh:
    ```bash
    platformio run
    ```
5.  Để xây dựng và tải lên bo mạch đã kết nối, chạy:
    ```bash
    platformio run --target upload
    ```

## 📈 Các cải tiến đã thực hiện

*   **Khắc phục lỗi biên dịch:** Đảm bảo thứ tự khởi tạo đối tượng chính xác trong `main.cpp`.
*   **Logic động cơ hai chiều:** Cập nhật lớp `Motor` để hỗ trợ các phương thức `forward()`, `reverse()`, và `stop()`.
*   **Xử lý nhiễu đầu vào:** Triển khai lớp `Button` với kỹ thuật debouncing không chặn để đọc chính xác trạng thái nút nhấn và công tắc hành trình.
*   **Cấu hình tập trung:** Di chuyển các giá trị cấu hình như thời gian chờ gia nhiệt và thời gian timeout động cơ vào `pinConfig.h`.
*   **Xử lý lỗi Timeout:** Thêm cơ chế timeout cho các chuyển động của động cơ, chuyển sang `ERROR_STATE` nếu công tắc hành trình không được kích hoạt trong thời gian quy định, tăng cường độ an toàn và ổn định của hệ thống.

## 📄 Giấy phép

Dự án này được cấp phép theo Giấy phép MIT. Xem tệp [LICENSE](LICENSE) để biết thêm chi tiết.
