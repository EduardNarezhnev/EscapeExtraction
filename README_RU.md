# Escape Extraction

Небольшая игра на Unreal Engine 5 для портфолио.

## Что это

Нужно собрать 3 ключа на уровне и дойти до зоны эвакуации. Если здоровье кончится — проигрыш. Если дойдёшь с ключами — победа.

## Управление

- WASD — движение
- Мышь — камера
- Space — прыжок
- Escape — пауза

## Что реализовано

- Персонаж от первого лица
- Система здоровья с полоской в HUD
- Ключи и аптечки
- Ловушки, которые активируются при приближении и преследуют игрока
- Победа, поражение, рестарт
- Меню паузы
- Звуки шагов, урона и лечения
- Красный экран при уроне, зелёный при лечении

## Технологии

Unreal Engine 5.6, C++(основная логика), Blueprint(для UI, звуков и эффектов), DataAsset(настройка баланса ловушек).

## Скриншоты и видео

![Уровень](Docs/screenshot_level.jpg)
![Ловушка1](Docs/screenshot_hazard_inactive.jpg)
![Ловушка2](Docs/screenshot_hazard_active.jpg)
![Предмет1](Docs/screenshot_pickup_1.jpg)
![Предмет2](Docs/screenshot_pickup_2.jpg)
![UI Во время игры](Docs/screenshot_ui_hud.jpg)
![UI Проигрыш](Docs/screenshot_ui_gameover_lose.jpg)
![UI Выигрыш](Docs/screenshot_ui_gameover_win.jpg)
![UI Меню паузы](Docs/screenshot_ui_pause.jpg)
![Пример кода](Docs/screenshot_cpp_source.jpg)

[Ссылка на YouTube](https://youtu.be/ducnEOf2lqw) - 2 минуты, показывает весь геймплей

## Скачать

[Ссылка на Google Drive](https://drive.google.com/file/d/1tEWpGDCybu7dlfBqDH-X8pq1K_WMJycf/view?usp=sharing)

**Платформа:** Windows 64-bit  

Распакуй архив и запусти `EscapeExtraction.exe`.

## Ограничения

- Один уровень (без сохранений).
- Нет настроек графики и управления.
- Только Windows 64-bit.

## Контакты

GitHub: [EduardNarezhnev](https://github.com/EduardNarezhnev)