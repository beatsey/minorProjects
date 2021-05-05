def addLetter(letter,wordArray):
    for i in range(len(wordArray)):
        for j in range(1,len(wordArray[i])+1):
            wordArray.append(letter+wordArray[i][:j]+letter+wordArray[i][j:])
        wordArray[i]=letter*2+wordArray[i]
        
def generateGaussWords(lastLetter):
    lastLetter=lastLetter.lower()
    if not lastLetter.isalpha():
        return False
    
    gaussWords=[lastLetter*2]
    for i in range(ord(lastLetter)-1,ord('a')-1,-1):
        addLetter(chr(i),gaussWords)
        
    return gaussWords

while True:
    letter=input('Please, provide exactly one english letter: ')
    if len(letter)==1 and letter.isalpha():
        break

# Список гауссовых слов, состоящих из a,b,..,letter
gaussWords = generateGaussWords(letter)
print("\n".join(gaussWords))