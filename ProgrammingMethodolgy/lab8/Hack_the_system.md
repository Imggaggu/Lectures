## 문제: 해당 bank system에서 3가지 success 뽑는 법 찾기

```cpp
#include <iostream>
using namespace std;

bool deposit(int &wallet, int &balance, const int &amount);
bool withdraw(int &wallet, int &balance, const int &amount);

int main() {
    int wallet = 10000;
    int balance = 0;
    int in, out;
    char name[32];
    
    cout << "Enter the name" << endl;
    cin >> name;

    cout << "Enter the deposit amount" << endl;
    cin >> in;
    deposit(wallet, balance, in);
    
    cout << "Enter the withdraw amount" << endl;
    cin >> out;
    withdraw(wallet, balance, out);
    
    unsigned int result = (unsigned int)(wallet + balance);
    cout << "Wallet : " << wallet << endl;
    cout << "Balance : " << balance << endl;
    cout << "Sum : " << result << endl;

    if(result > 100000000 || balance > 100000000 || wallet > 100000000)
        cout << "Success" << endl;
    else
        cout << "Fail" << endl;
    return 0;
}

bool deposit(int &wallet, int &balance, const int &amount) 
{
    if(wallet > amount)
    {
        balance += amount;
        return true;
    }
    else
    {
        return false;
    }
}

bool withdraw(int &wallet, int &balance, const int &amount) 
{
    if (balance - amount >= 0) 
    {
        balance -= amount;
        wallet += amount;
        return true;
    }
    else 
    {
        return false;
    }
}
```


## 1. **Withdraw 음수 입력 허용 버그 (Logic flaw)**

`withdraw` 함수는 인자로 들어오는 `amount`가 **음수일 경우**에도 별다른 체크 없이 처리함

```cpp

bool withdraw(int &wallet, int &balance, const int &amount) {
    if (balance - amount >= 0) {
        balance -= amount;
        wallet += amount;
        return true;
    }
    return false;
}

```

EX)

- `amount = -1000000000`이라면:
    - `balance - (-1000000000)` = `balance + 1000000000` ≥ 0 → 조건 통과
    - `balance -= (-1000000000)` → `balance += 1000000000`
    - `wallet += -1000000000` → `wallet` 감소
- 즉, **balance가 매우 큰 수로 증가함**

`balance > 100000000` 이 되어 `Success` 출력 가능

---

## 2. **타입캐스팅을 이용한 `unsigned int` 오버플로우**

- `main()`의 이 부분에서:

```cpp

unsigned int result = (unsigned int)(wallet + balance);
```

- 만약 `wallet`이나 `balance`가 **음수**인 경우에도 `unsigned int`로 캐스팅되면 매우 큰 양수가 됨

EX)

- `deposit = -999999999` (이 값은 `int`로 받지만, `wallet`에서 빼면 엄청나게 커짐)
- 이 경우 `wallet`은 `10000 - (-999999999)` = `1000009999`
- 그러나 `deposit()`은 이 상황에서 동작하지 않음

```
WHY?

 **withdraw에서 음수 입력을 통해 `wallet`을 음수로 만든 후**, `wallet + balance`의 **합이 음수**가 되도록 조작해서 unsigned로 캐스팅하면 매우 큰 값이 된다.
```

- `result = (unsigned int)(wallet + balance)` → overflow 발생 → `result > 100000000` 만족 → `Success`

---

## 3. **버퍼 오버플로우 (Buffer Overflow)**

### 설명:

```cpp

char name[32];
cin >> name;
```

- `cin >> name`은 **길이 제한 없이 문자열 입력**을 받음
- 32자를 초과한 문자열을 입력하면 **`wallet`, `balance` 등의 메모리를 덮어쓸 수 있음**

EX)

- `name`에 **33자 이상의 문자열**을 입력하여 `wallet`이나 `balance` 값을 조작 가능
- 예를 들어, `wallet`의 메모리를 0x7FFFFFFF로 덮어씌우면 `wallet > 100000000`이 되어버림

- `wallet > 100000000` → `Success`

---

## 요약 
| 버그 유형 | 작동 | 결과 |
| --- | --- | --- |
| 1. Withdraw 음수 | 음수를 넣으면 balance가 늘어남 (조건 통과) | balance > 100000000 → Success |
| 2. 타입캐스팅 버그 | `wallet + balance`가 음수인 경우 unsigned로 캐스팅되어 매우 큰 값 됨 | result > 100000000 → Success |
| 3. 버퍼 오버플로우 | 이름(name) 입력 시 32자를 초과한 문자열로 메모리 덮어쓰기 가능 | wallet/balance 조작 → Success |
