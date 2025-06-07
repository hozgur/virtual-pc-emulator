# Virtual PC Emulator

Bu proje, 32-bit register ve 24-bit adresleme kullanan bir sanal CPU üzerine kurulu basit bir **virtual PC emülatörüdür**. Bellek haritası, I/O register'ları ve video çıkışı gibi temel sistem bileşenlerini içerir.

## 📦 İçerik

- `emulator.h`: CPU ve mesajlaşma yapısı
- `memory_map.h`: Bellek ve I/O adres tanımları
- `video_controller.c`: Text-mode video belleği ve terminal çıktısı
- `call_ret_example.c`: CALL & RET komutlarını örnekleyen program yükleyici
- `main.c`: Programı başlatan ana fonksiyon
- `CMakeLists.txt`: Derleme için CMake yapılandırması

## 🔧 Derleme Talimatları

```bash
mkdir build
cd build
cmake ..
make
./virtual_pc
```

> Derlemek için `gcc` ve `cmake` kurulu olmalıdır.

## 🎮 Video Belleği

Text-mode video RAM belleği 80x25 boyutundadır. `video_render_text_terminal()` fonksiyonu terminale içerikleri yazdırır.

## 💻 Örnek Program

`call_ret_example.c` şu işlemleri yapar:

- A register'ına `10` yükler
- Subroutine'e `CALL` eder
- Alt program `Z` ile `A`'yı toplar (`Z = 5`)
- `RET` komutu ile geri döner
- `HLT` komutu ile işlemci durur

Çıktı olarak:
```
Program çalıştırılıyor...
Program sona erdi. A = 15
```

---

© 2025 Hakan Özgür. Tüm hakları saklıdır.
