#include <iostream>
#include <vector>
#include <algorithm>
typedef std::vector<std::vector<int>> board;
typedef std::vector<std::vector<int>> block;

using namespace std;

block rotateBlock(block b) {
    block r = block (b[0].size(), vector<int>(b.size(),0));
    
    for (int i=0; i<r[0].size(); ++i) {
        for (int j=0; j<r.size(); ++j) {
            r[j][i] = b[i][j];
        }
    }
    for (int i=0; i<r.size(); ++i) {
        reverse(r[i].begin(), r[i].end());
    }
    return r;
}

vector<vector<int>> insertBlock(vector<vector<int>> brd, vector<vector<int>> block, int horOffset) {
    int insertPosition = 0;
    
    for (int h=0; h<brd[0].size()-block[0].size()+1; ++h) {
        for (int i=0; i<block[0].size(); ++i) {
            for (int j=0; j<block.size(); ++j) {
                if (block[j][i] == 1) {
                    for (int k=h+i; k >= 0; --k) {
                        if (brd[horOffset+j][k] == 1) {
                            insertPosition = h-1;
                            goto insert;
                        }
                    }
                }
            }
        }
    }
    insertPosition = brd[0].size()-block[0].size();
    
insert:
    if (insertPosition<0) return vector<vector<int>>(0, vector<int>(0));
    
    for (int i=0; i<block[0].size(); ++i) {
        for (int j=0; j<block.size(); ++j) {
            if (block[j][i] == 1)
                brd[horOffset+j][insertPosition+i] = block[j][i];
        }
    }
    
    return brd;
}

int eraseLines(board* brd) {
    int removed = 0;
    for (int i=0; i<(*brd)[0].size(); ++i) {
        bool removeable = true;
        for (int j=0; j<brd->size(); ++j) {
            if ((*brd)[j][i] == 0) {
                removeable = false;
                break;
            }
        }
        if (removeable) {
            ++removed;
            for (int j=0; j<brd->size(); ++j) {
                (*brd)[j].erase((*brd)[j].begin() + i);
                (*brd)[j].insert((*brd)[j].begin(), 0);
            }
        }
    }
    return removed;
}

int backtrack(board brd, vector<block> blocks) {
    if (blocks.size() == 0) {
        
        return 0;
    }
    block blk = blocks[0];
    blocks.erase(blocks.begin());
    
    vector<block> rotBlock;
    rotBlock.push_back(blk);
    
    block rotated = rotateBlock(blk);
    if (rotated != blk)
        rotBlock.push_back(rotated);
    
    rotated = rotateBlock(rotated);
    if (rotated != blk)
        rotBlock.push_back(rotated);
    
    rotated = rotateBlock(rotated);
    if (rotated != blk)
        rotBlock.push_back(rotated);
    
    int maxSum = 0;
    
    for (int i=0; i<rotBlock.size(); ++i) {
        block b = rotBlock[i];
        for (int j=0; j<brd.size()-b.size()+1; ++j) {
            board newBoard = insertBlock(brd, b, j);
            if (newBoard.size() == 0 || newBoard[0].size() == 0) continue;
            int erased = eraseLines(&newBoard);
            erased += backtrack(newBoard, blocks);
            if (erased > maxSum) maxSum = erased;
        }
    }
    
    return maxSum;
}




int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for (int ti=1; ti<=t; ++ti) {
        int n;
        cin >> n;
        int wb,hb;
        cin >> wb >> hb;
        vector<vector<int>> board(wb, vector<int>(hb,0));
        for (int i=0; i<hb; ++i) {
            for (int j=0; j<wb; ++j) {
                char c;
                cin >> c;
                if (c == 'X') board[j][i] = 1;
            }
        }
        vector<vector<vector<int>>> blocks(n);
        for (int i=0; i<n; ++i) {
            int hi,wi;
            cin >> wi >> hi;
            blocks[i] = vector<vector<int>>(wi, vector<int>(hi,0));
            for (int j=0; j<hi; ++j) {
                for (int k=0; k<wi; ++k) {
                    char c;
                    cin >> c;
                    if (c == 'X') {
                        blocks[i][k][j] = 1;
                    }
                }
            }
        }
        
        
        
        int maxPossibleLines = backtrack(board, blocks);
        
        cout << "Case #" << ti << ": " << maxPossibleLines << "\n";
    }
    return 0;
}