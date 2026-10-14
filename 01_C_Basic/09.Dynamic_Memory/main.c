#include <stdio.h>
#include <stdlib.h>

void Dynamic_Integer_Single()
{
    // malloc(): 필요한 메모리를 할당하고 주소를 반환함
    int *ptr = malloc(sizeof(int));

    if (ptr == NULL)
    {
        // malloc 실패 시 종료
        printf("Memory allocation failed\n");
        return;
    }

    *ptr = 100;
    printf("Value: %d\n", *ptr);

    // free(): 동적으로 할당한 메모리를 더 이상 사용하지 않을 때 반환
    free(ptr);
    // 포인터가 해제된 메모리를 가리키는 상태로 남지 않게 정리한다.
    // 이는 포인터 변수만 초기화하는 것이지 해제된 메모리를 다시 유효하게 만드는 것은 아니다.
    ptr = NULL;
}

// 메모리 배열 할당
void Dynamic_Integer_Array()
{
    int array_size = 5;
    int value[5] = {10, 20, 30, 40, 50};
    int *arr = malloc(array_size * sizeof(int));


    if (arr == NULL)
    {
        // malloc 실패 시 종료
        printf("Memory allocation failed\n");
        return;
    }

    for (int i = 0; i < array_size; i++)
    {
        arr[i] = value[i];
        printf("Array Value: %d\n", *(arr + i));
    }

    free(arr);
    arr = NULL;
}

// 의도적 오류 확인
void Use_After_Free()
{
    int array_size = 5;
    int value[5] = {1, 2, 3, 4, 5};
    int *arr = malloc(array_size * sizeof(int));

    if (arr == NULL)
    {
        // malloc 실패 시 종료
        printf("Memory allocation failed\n");
        return;
    }

    for (int i = 0; i < array_size; i++)
    {
        arr[i] = value[i];
        printf("Array Value: %d\n", *(arr + i));
    }

    free(arr);
    printf("%d\n", arr[0]);

    return;
}

// 메모리 누수
void Memory_Leak()
{
    int *value_memory = malloc(sizeof(int));

    if (value_memory == NULL)
    {
        // malloc 실패 시 종료
        printf("Memory allocation failed\n");
        return;
    }

    *value_memory = 100;
    printf("Value: %d\n", *value_memory);

    return;
}

int main(void)
{
    Dynamic_Integer_Single();
    Dynamic_Integer_Array();
    Use_After_Free();
    Memory_Leak();
    return 0;
}