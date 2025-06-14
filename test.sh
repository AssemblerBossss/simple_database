#!/bin/bash

# Функция для запуска тестового сценария
run_script() {
    local commands=("$@")
    local output=""

    # Создаем FIFO для взаимодействия с процессом
    local fifo=$(mktemp -u)
    mkfifo "$fifo"

    # Запускаем процесс в фоне
    ./cmake-build-debug/database < "$fifo" > output.txt &
    local pid=$!

    # Открываем FIFO на запись
    exec 3>"$fifo"

    # Посылаем команды
    for cmd in "${commands[@]}"; do
        echo "$cmd" >&3
    done

    # Закрываем канал
    exec 3>&-
    wait $pid

    # Читаем результат
    mapfile -t output_lines < output.txt
    rm -f "$fifo" output.txt

    printf '%s\n' "${output_lines[@]}"
}

# Тест вставки и выборки
test_insert_and_select() {
    echo "Running test: insert and retrieve a row"

    # Запускаем тестовый сценарий
    local result=()
    mapfile -t result < <(run_script \
        "insert 1 user1 person1@example.com" \
        "select" \
        ".exit")

    # Ожидаемый результат
    local expected=(
        "db > Executed."
        "db > (1, user1, person1@example.com)"
        "Executed."
        "db > "
    )

    # Проверяем результаты
    local pass=1
    for i in "${!expected[@]}"; do
        if [[ "${result[i]}" != "${expected[i]}" ]]; then
            echo "FAIL: Line $((i+1))"
            echo "  Expected: '${expected[i]}'"
            echo "  Got:      '${result[i]}'"
            pass=0
        fi
    done

    if [[ $pass -eq 1 ]]; then
        echo "PASS: All outputs match"
        return 0
    else
        return 1
    fi
}

# Запускаем тест
test_insert_and_select