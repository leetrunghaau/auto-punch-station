# Tài liệu Sơ đồ nguyên lý

## Tổng quan Sơ đồ nguyên lý Bộ điều khiển máy dập

Sơ đồ này triển khai một **hệ thống điều khiển AC đa kênh** dựa trên ATmega328P, có khả năng:

- Điều khiển tới **8 tải AC** (động cơ, bộ gia nhiệt, đèn)
- Đọc tới **8 đầu vào kỹ thuật số cách ly quang**
- Phát hiện điểm không (zero-crossing) để điều khiển pha AC
- Cung cấp đèn LED trạng thái cho mỗi kênh
- Logic cách ly thông qua bộ cách ly quang

---

## 🔹 1. Nguồn điện

### HLK-10M05
- **Mục đích:** Chuyển đổi AC 220V sang DC 5V
- **Đầu ra:**
  - +5V DC (VCC_2)
  - GND

**Tụ lọc:**
- C3, C4, C12

**Sử dụng:**
- Cấp nguồn cho MCU, bộ cách ly quang, mạch logic

---

## 🔹 2. Phần MCU

### ATmega328P
- **Vai trò:** Bộ điều khiển trung tâm
- **Tính năng:**
  - 32 chân IO kỹ thuật số
  - Giao tiếp nối tiếp UART
  - Giao diện lập trình SPI ISP
  - Xung nhịp: Thạch anh 16 MHz (Y1) + tụ C7/C11
  - Mạch reset: Điện trở kéo lên + tụ điện
- **Nguồn:** +5V từ HLK-10M05

**Các chân quan trọng:**
- Đầu ra kỹ thuật số đến MOC3063M để điều khiển AC
- Đầu vào kỹ thuật số từ EL357 để phản hồi cảm biến
- Các chân SPI để lập trình

---
## 🔹 3. Điều khiển đầu ra (Động cơ AC)

**Mỗi động cơ AC được điều khiển bởi 2 MOC3063M + 2 Triac công suất, để thực hiện chức năng đảo chiều:**

- **MOC3063M:**
  - **Đầu vào:**
    - **Chân 1:** +5V qua điện trở hạn dòng
    - **Chân 2:** Tín hiệu điều khiển từ MCU (kéo GND để kích hoạt)
    - **Chân 6:** Nối dây lửa AC qua điện trở 360Ω (để phát hiện điểm không)
  - **Đầu ra:**
    - **Chân 4:** Tín hiệu kích Gate của Triac BT16-800B

- **BT16-800B (Triac công suất):**
  - **Chân G:** Nhận tín hiệu kích từ MOC3063M
  - **Chân A1 / A2:** Được đấu với cuộn khởi động (start winding) của động cơ AC, để đảo chiều

**Nguyên lý:**
- **Mỗi động cơ AC sử dụng 2 MOC3063M và 2 Triac để đảo chiều quay.**
- Trong thực tế:
  - MOC + Triac số 1 điều khiển trạng thái quay thuận (nối cuộn khởi động theo chiều thuận)
  - MOC + Triac số 2 điều khiển trạng thái quay nghịch (nối cuộn khởi động đảo cực)
- **Chỉ được phép kích hoạt 1 cặp MOC/Triac tại một thời điểm để tránh chập mạch.**

**Đèn LED trạng thái:**
- Nối song song LED trong MOC3063M (qua điện trở)
- Sáng khi kênh tương ứng được kích hoạt

---

## 🔹 4. Bảng ánh xạ chân điều khiển MCU

| Động cơ | MOC3063M | Chân điều khiển MCU | Chức năng |
|---|---|---|---|
| Motor 1 | U1 | D5 | Quay thuận |
| Motor 1 | U2 | D7 | Quay nghịch |
| Motor 2 | U4 | D6 | Quay thuận |
| Motor 2 | U5 | D8 | Quay nghịch |


**Ghi chú:**
- Chân phát hiện điểm không của MOC3063M được kết nối (một số kênh)
- Mỗi đầu ra EL357 nối tiếp với một điện trở và đèn LED
- Tải đầu ra được kết nối với nguồn AC thông qua Triac

---

## 🔹 4. Điều khiển đầu vào (Cảm biến / Công tắc hành trình)

**Mỗi tín hiệu đầu vào:**
- Đi qua một bộ cách ly quang EL357
  - Cách ly mạch ngoài khỏi MCU
- Kéo lên VCC thông qua điện trở 10k

**Tổng số đầu vào: 8**

| Tham chiếu đầu vào | Tên tín hiệu | Chân MCU |
|---|---|---|
| A_O | Đầu vào A | D4 |
| B_O | Đầu vào B | D3 |
| C_O | Đầu vào C | D2 |
| D_O | Đầu vào D | A5 |
| E_O | Đầu vào E | A4 |
| F_O | Đầu vào F | A3 |
| G_O | Đầu vào G | A1 |
| H_O | Đầu vào H | A2 |

**Ví dụ sử dụng:**
- Công tắc hành trình Dập Xuống
- Công tắc hành trình Dập Lên
- Băng tải Bắt đầu
- Băng tải Kết thúc
- Nút khởi động
- Dừng khẩn cấp

---

## 🔹 5. Mạch phát hiện điểm không

**Mục đích:**
- Phát hiện các sự kiện điểm không của AC
- Cho phép kích hoạt Triac theo pha (điều khiển PWM trong tương lai)

**Các thành phần:**
- 4x MOC3063M được nối dây để phát hiện điểm không
- Đầu ra có thể được đưa vào các chân ngắt của MCU

**Tham chiếu:**
- U1, U2, U4, U5

---

## 🔹 6. Đèn LED trạng thái

**Mỗi kênh đầu ra có:**
- Đèn LED (0805) nối tiếp với điện trở 2k
- Sáng lên khi kênh hoạt động

**Mục đích:**
- Xác nhận trực quan trạng thái BẬT/TẮT của đầu ra

---

## 🔹 7. Giao tiếp & Lập trình

**Giao tiếp nối tiếp:**
- Các chân TXD, RXD được đưa ra ngoài
- Được sử dụng để giám sát và gỡ lỗi

**Giao diện ISP:**
- Các chân SPI (MISO, MOSI, SCK)
- Hỗ trợ tải firmware thông qua bộ lập trình

---

## 🔹 8. Đề xuất ánh xạ đầu ra

| Chức năng | Kênh EL357 | Chân MCU | Ghi chú |
|---|---|---|---|
| Bộ gia nhiệt | *4 | D4 | Tải AC đầu ra 1 |
| Động cơ dập | *5 | D3 | Tải AC đầu ra 2 |
| Động cơ băng tải | *6 | D2 | Tải AC đầu ra 3 |
| Đèn báo | *7 | A5 | Tải AC đầu ra 4 |
| (Trống) | *8 | A4 | Kênh dự phòng |
| (Trống) | *9 | A3 | Kênh dự phòng |
| (Trống) | *10 | A1 | Kênh dự phòng |
| (Trống) | *11 | A2 | Kênh dự phòng |

---


## 📝 Ghi chú về chân A0
- Chân **A0** được dùng để **giám sát tín hiệu nguồn AC** (thường qua mạch chia áp + opto).
- Khi nguồn AC mất, tín hiệu A0 sẽ chuyển mức thấp, MCU có thể dừng toàn bộ hệ thống.

---

## 🔹 9. Các mở rộng tùy chọn

- Kết nối đầu ra Zero-Cross với MCU để điều khiển pha
- Sử dụng các kênh không sử dụng cho các động cơ hoặc bộ gia nhiệt bổ sung
- Thêm EEPROM để cấu hình
- Tích hợp màn hình OLED

---

## ⚠ Lưu ý an toàn

- Tất cả hệ thống dây điện AC phải được thực hiện với cách điện thích hợp
- Cách ly quang bảo vệ MCU nhưng không bảo vệ hệ thống dây rơle
- Đảm bảo nối đất khung gầm đúng cách
- Sử dụng cầu chì và bộ ngắt mạch để bảo vệ quá tải

---

## 📝 Tham khảo

- Sơ đồ nguyên lý `schematic.pdf`
- Bảng dữ liệu MOC3063M
- Bảng dữ liệu EL357

