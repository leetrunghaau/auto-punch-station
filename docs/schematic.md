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
- Đầu ra kỹ thuật số đến EL357 để điều khiển AC
- Đầu vào kỹ thuật số từ EL357 để phản hồi cảm biến
- Các chân SPI để lập trình

---

## 🔹 3. Điều khiển đầu ra (Tải AC)

**Mỗi kênh tải AC bao gồm:**
- Bộ cách ly quang EL357
  - **Đầu vào:** Chân đầu ra của MCU
  - **Đầu ra:** Kích hoạt đèn LED MOC3063M
- MOC3063M (Trình điều khiển Opto-Triac với tính năng phát hiện điểm không)
  - **Đầu vào:** Từ EL357
  - **Đầu ra:** Điều khiển Triac bên ngoài (không hiển thị)
- Đèn LED trạng thái để chỉ báo đầu ra BẬT

**Tổng số kênh: 8**

| Kênh số | Tham chiếu EL357 | Tham chiếu MOC3063M | Chân điều khiển MCU |
|---|---|---|---|
| 1 | *4 | U1 | D4 |
| 2 | *5 | U2 | D3 |
| 3 | *6 | U4 | D2 |
| 4 | *7 | U5 | A5 |
| 5 | *8 | - | A4 |
| 6 | *9 | - | A3 |
| 7 | *10 | - | A1 |
| 8 | *11 | - | A2 |

**Ghi chú:**
- Chân phát hiện điểm không của MOC3063M được kết nối (một số kênh)
- Mỗi đầu ra EL357 nối tiếp với một điện trở và đèn LED
- Tải đầu ra được kết nối với nguồn AC thông qua Triac

---

## 🔹 4. Điều khiển đầu vào (Cảm biến / Công tắc hành trình)

**Mỗi tín hiệu đầu vào:**
- Đi qua một bộ cách ly quang EL357
  - Cách ly mạch ngoài khỏi MCU
- Kéo lên VCC thông qua điện trở

**Tổng số đầu vào: 8**

| Tham chiếu đầu vào | Tên tín hiệu | Chân MCU |
|---|---|---|
| A_O | Đầu vào A | D3 |
| B_O | Đầu vào B | D4 |
| C_O | Đầu vào C | A5 |
| D_O | Đầu vào D | A1 |
| E_O | Đầu vào E | A3 |
| F_O | Đầu vào F | A4 |
| G_O | Đầu vào G | A2 |
| H_O | Đầu vào H | (Tùy chọn) |

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