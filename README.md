# Bioinformatics

## Introduction
생물정보학에 필요한 프로그램 구현 소스

## Contents

### Algorithms
* Needleman–Wunsch
  * 시퀀스 정렬을 위한 Dynamic programming을 적용한 프로그램
  
### ComparingSequences <br>
* LCS기반 Dynamic programming을 적용한 프로그램
  * FASTA 포맷 기반 입력 데이터를 가공함
  * 두개의 입력 데이터를 서로 비교하여 시퀀스 매칭함
  * 시퀀스 매칭의 방법은 local alignment, global alignment 
    
* 실행 명령어 
  * $[실행파일] [입력파일1] [입력파일2]
  * $a.out /0.InputData/NC_011353.faa /0.InputData/NC_011353.faa

### StrCluster
* 미입력
