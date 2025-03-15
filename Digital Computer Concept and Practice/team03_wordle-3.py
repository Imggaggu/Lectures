class WordleSolver:
    def __init__(self):
        with open('dictionary.txt', 'r') as f:
            dic_file = f.readlines()
        self.dic = list(map(lambda x: x.strip(), dic_file))
        self.idx = 0
        # 초기 추측 : salet -> 단어 정보 기댓값에 의거
        self.current_guess = 'salet'
        # 단어 리스트 원본 복사
        self.bef_dic = []
        for i in range(len(self.dic)):
            self.bef_dic.append(self.dic[i])
        self.bef_guess = ''
    
    # 'salet'로 시작하는 추측 반환
    def start(self):
        return self.current_guess

    def all_words_letter_apart(self):
        # self.dic 내의 모든 단어들의 패턴 파악
        differences_count = {1: 0, 2: 0, 3: 0}
        for i in range(len(self.dic)):
            for j in range(i + 1, len(self.dic)):
                differences = sum(1 for a, b in zip(self.dic[i], self.dic[j]) if a != b)
                if differences in differences_count:
                    differences_count[differences] += 1
                else:
                    return None  # 동일한 패턴 없을 시

        # 가장 많이 발생한 차이의 글자 수 반환 : 4글자 패턴 반복이면 1, 3글자 패턴 반복이면 2, 2글자 패턴 반복이면 3
        max_diff_count = max(differences_count, key=differences_count.get)
        return max_diff_count if differences_count[max_diff_count] > 0 else None
    
    def for_B(self):
        # 2개 글자 패턴 반복일 때, 나머지 글자들의 교집합이 가장 많은 글자를 추측
        common_letters = set(self.dic[0])
        different_letters = set()
        for word in self.dic[1:]:
            common_letters.intersection_update(word)
            for word in self.dic:
                for letter in word:
                    if letter not in common_letters:
                        different_letters.add(letter)

        # self.bef_dic에서 different_letters를 가장 많이 포함하는 단어 탐색
        if len(different_letters) != 0:
            max_intersection = 0
            max_word = None
            for word in self.bef_dic:
                intersection_count = len(set(word) & different_letters)
                if intersection_count > max_intersection:
                    max_intersection = intersection_count
                    max_word = word
            return max_word
        else:
            return self.dic[0]
   
    def guess(self, prev):
        # 'B'에 대한 처리 및 확정된 위치 추적
        confirmed_positions = [i for i, feedback in enumerate(prev) if feedback == 'B']
        for i in confirmed_positions:
            self.dic = [word for word in self.dic if word[i] == self.current_guess[i]]
        
        # 중복 알파벳 처리 로직
        for char in set(self.current_guess):
            if self.current_guess.count(char) > 1:  # 중복 알파벳인지 확인
                indices = [i for i, l in enumerate(self.current_guess) if l == char]
                feedbacks = [prev[i] for i in indices]

                # 모든 중복된 알파벳 평가 결과가 'G'인 경우
                if all(f == 'G' for f in feedbacks):
                    self.dic = [word for word in self.dic if char not in word]
                
                # 중복된 알파벳의 평가 결과에 'Y'와 'G'가 섞여 있는 경우 -> B도 섞여있는지 확인
                elif 'Y' in feedbacks and 'G' in feedbacks:
                    y_count = feedbacks.count('Y')
                    b_count = feedbacks.count('B')
                    
                    # B가 없다면? : Y와 G만 찾아 self.dic에서 필터링
                    if b_count == 0:
                        for index in indices:
                            if prev[index] == 'Y':
                                self.dic = [word for word in self.dic if word[index] != char]
                        self.dic = [word for word in self.dic if char in word and word.count(char) == y_count]
                    
                    # B가 있다면? : Y 최우선 처리, B의 개수 + Y의 개수만큼 알파벳 남겨두고 필터링 + B의 위치로 추가 필터링
                    elif b_count > 0:
                        for index in indices:
                            if prev[index] == 'Y':
                                self.dic = [word for word in self.dic if word[index] != char]
                        self.dic = [word for word in self.dic if char in word and word.count(char) == (b_count + y_count)]
                        for index in indices:
                            if prev[index] == 'B':
                                self.dic = [word for word in self.dic if word[index] == char]
                                        
                # 중복된 알파벳의 평가 결과에 'B'와 'G'가 섞여 있는 경우 -> 'Y'는 없음
                elif 'B' in feedbacks and 'G' in feedbacks:
                    temp = []
                    for index in indices:
                        if prev[index] == 'B':
                            self.dic = [word for word in self.dic if word[index] == char]
                            temp.append(index)
                    for i in range(5):
                        if i not in temp:
                            self.dic = [word for word in self.dic if word[i] != char]    

        # 'Y' (잘못된 위치) 및 'G' (없음)
        for i, feedback in enumerate(prev):
            temp_position = [pos for pos in range(5) if pos not in confirmed_positions]
            char = self.current_guess[i]
            if feedback == 'G':
                if i not in confirmed_positions:
                    for j, current in enumerate(self.current_guess): #cg=abeam
                        if i==j: continue
                        if char==current: break
                    else:
                        self.dic = [word for word in self.dic if all(char != word[pos] for pos in temp_position)]
            elif feedback == 'Y':
                if i not in confirmed_positions:
                    self.dic = [word for word in self.dic if word[i] != char and any(char == word[pos] for pos in temp_position)]

        # 이미 시도한 단어 제거
        if self.current_guess in self.dic:
            self.dic.remove(self.current_guess)
        
        diff_count = self.all_words_letter_apart()
        
        if diff_count != 0 and len(self.dic) >= 3:
            self.bef_guess = self.current_guess
            self.current_guess = self.for_B()
            self.bef_dic.remove(self.current_guess)
            return self.current_guess

        else:
            # 필터링된 목록에서 다음 추측 반환 -> 가능하면 중복 알파벳 없도록 (self.dic 개수가 8개가 넘으면, 중복 없게 추측)
            if len(self.dic) > 8:
                ret_temp = 0
                while(ret_temp < len(self.dic)):
                    count = 0
                    for char in set(self.dic[ret_temp]):
                        if self.dic[ret_temp].count(char) > 1:
                            ret_temp += 1
                            count = 1
                            break
                    if count == 0:
                        self.current_guess = self.dic[ret_temp]
                        return self.current_guess
            
            self.current_guess = self.dic[0]
            return self.current_guess
            
