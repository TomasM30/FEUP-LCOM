#include "chess.h"

void load_board() {
    board[0][0] = (Piece) {ROOK, BLACK};
    board[0][1] = (Piece) {KNIGHT, BLACK};
    board[0][2] = (Piece) {BISHOP, BLACK};
    board[0][3] = (Piece) {QUEEN, BLACK};
    board[0][4] = (Piece) {KING, BLACK};
    board[0][5] = (Piece) {BISHOP, BLACK};
    board[0][6] = (Piece) {KNIGHT, BLACK};
    board[0][7] = (Piece) {ROOK, BLACK};
    for (int i = 0; i < 8; i++) {
        board[1][i] = (Piece) {PAWN, BLACK};
    }

    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = (Piece) {EMPTY, UNDEFINED};
        }
    }

    for (int i = 0; i < 8; i++) {
        board[6][i] = (Piece) {PAWN, WHITE};
    }
    board[7][0] = (Piece) {ROOK, WHITE};
    board[7][1] = (Piece) {KNIGHT, WHITE};
    board[7][2] = (Piece) {BISHOP, WHITE};
    board[7][3] = (Piece) {QUEEN, WHITE};
    board[7][4] = (Piece) {KING, WHITE};
    board[7][5] = (Piece) {BISHOP, WHITE};
    board[7][6] = (Piece) {KNIGHT, WHITE};
    board[7][7] = (Piece) {ROOK, WHITE};
}

int draw_board() {
    if (draw_sprite(board_img, 0, 0)) return 1;
    vg_copy_buffer();
    return 0;
}

int draw_pieces() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece piece = board[i][j];
            
            if (piece.type == EMPTY) continue;

            if (draw_piece(i, j, piece.color)) return 1;
        }
    }
    vg_copy_buffer();


    return 0;
}

void select_piece(int x, int y) {
    int row = y / SQUARE_SIZE;
    int col = x / SQUARE_SIZE;

    if (row < 0 || row > 7 || col < 0 || col > 7) return;

    Piece piece = board[row][col];

    if (piece.type == EMPTY) return;

    if (piece.color == WHITE && !white_turn) return;

    if (piece.color == BLACK && white_turn) return;

    sel_row = row;
    sel_col = col;

    selected = true;

    return;
}

void deselect_piece() {
    sel_row = -1;
    sel_col = -1;

    selected = false;
}

bool is_selected() {
    return selected;
}

void move_piece(int xf, int yf) {
    if (!selected) return;

    int row = yf / SQUARE_SIZE;
    int col = xf / SQUARE_SIZE;

    if (row < 0 || row > 7 || col < 0 || col > 7) return;

    if (row == sel_row && col == sel_col) return;

    if (is_valid_move(row, col)) {
        board[row][col] = board[sel_row][sel_col];
        board[sel_row][sel_col] = (Piece) {EMPTY, UNDEFINED};
        white_turn = !white_turn;
    }

    deselect_piece();
}

bool is_valid_move(int row, int col) {
    Piece piece = board[sel_row][sel_col];

    switch (piece.type) {
    
        default:
            return false;
    }
}


/* Auxiliary drawing functions */

int draw_piece(int i, int j, uint32_t color) {
    switch (board[i][j].type) {
        case KING:
            return draw_king(j * SQUARE_SIZE, i * SQUARE_SIZE, color);
        case QUEEN:
            return draw_queen(j * SQUARE_SIZE, i * SQUARE_SIZE, color);
        case BISHOP:
            return draw_bishop(j * SQUARE_SIZE, i * SQUARE_SIZE, color);
        case KNIGHT:
            return draw_knight(j * SQUARE_SIZE, i * SQUARE_SIZE, color);
        case ROOK:
            return draw_rook(j * SQUARE_SIZE, i * SQUARE_SIZE, color);
        case PAWN:  
            return draw_pawn(j * SQUARE_SIZE, i * SQUARE_SIZE, color);

        default:
            return 0;
    }
}

int draw_king(int x, int y, uint32_t color) {
    if (color == BLACK) {
        if (draw_sprite(bK, x, y)) return 1;
    } else {
        if (draw_sprite(wK, x, y)) return 1;
    }

    return 0;
}

int draw_queen(int x, int y, uint32_t color) {
    if (color == BLACK) {
        if (draw_sprite(bQ, x, y)) return 1;
    } else {
        if (draw_sprite(wQ, x, y)) return 1;
    }

    return 0;
}

int draw_bishop(int x, int y, uint32_t color) {
    if (color == BLACK) {
        if (draw_sprite(bB, x, y)) return 1;
    } else {
        if (draw_sprite(wB, x, y)) return 1;
    }

    return 0;
}

int draw_knight(int x, int y, uint32_t color) {
    if (color == BLACK) {
        if (draw_sprite(bN, x, y)) return 1;
    } else {
        if (draw_sprite(wN, x, y)) return 1;
    }

    return 0;
}

int draw_rook(int x, int y, uint32_t color) {
    if (color == BLACK) {
        if (draw_sprite(bR, x, y)) return 1;
    } else {
        if (draw_sprite(wR, x, y)) return 1;
    }

    return 0;
}

int draw_pawn(int x, int y, uint32_t color) {
    if (color == BLACK) {
        if (draw_sprite(bP, x, y)) return 1;
    } else {
        if (draw_sprite(wP, x, y)) return 1;
    }

    return 0;
}
