##  Here’s what the layout of a leaf node looks like currently
![Скриншот приложения](images/leaf-node-format.png)\

### Заголовок узла (первые 10 байт)
| byte 0    | byte 1    | bytes 2-5    | bytes 6-9   |
|-----------|-----------|--------------|-------------|
| node_type | is_root   | parent_pointer | num_cells |

- **node_type** (1 байт): Тип узла (лист/внутренний)
- **is_root** (1 байт): Флаг корневого узла
- **parent_pointer** (4 байта): Указатель на родительский узел
- **num_cells** (4 байта): Количество ячеек (key-value пар) в узле


### Тело узла (ячейки)

| bytes 10-13    | bytes 14-306    |
|----------------|-----------------|
| key 0          | value 0         |
 
- Ячейки расположены последовательно
- Между value и следующим key нет промежутков