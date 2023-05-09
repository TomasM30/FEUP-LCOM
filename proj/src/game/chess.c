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

    return 0;
}

int draw_pieces() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8 ; j++) {
            Piece piece = board[i][j];
            if (piece.type == EMPTY) continue;

            switch (piece.type) {
                case PAWN:
                    if (piece.color == BLACK) {
                        if (draw_sprite(bP, j * 108, i * 108)) return 1;
                    } else {
                        if (draw_sprite(wP, j * 108, i * 108)) return 1;
                    }
                    break;
                case ROOK:
                    if (piece.color == BLACK) {
                        if (draw_sprite(bR, j * 108, i * 108)) return 1;
                    } else {
                        if (draw_sprite(wR, j * 108, i * 108)) return 1;
                    }
                    break;
                case KNIGHT:
                    if (piece.color == BLACK) {
                        if (draw_sprite(bN, j * 108, i * 108)) return 1;
                    } else {
                        if (draw_sprite(wN, j * 108, i * 108)) return 1;
                    }
                    break;
                case BISHOP:
                    if (piece.color == BLACK) {
                        if (draw_sprite(bB, j * 108, i * 108)) return 1;
                    } else {
                        if (draw_sprite(wB, j * 108, i * 108)) return 1;
                    }
                    break;
                case QUEEN:
                    if (piece.color == BLACK) {
                        if (draw_sprite(bQ, j * 108, i * 108)) return 1;
                    } else {
                        if (draw_sprite(wQ, j * 108, i * 108)) return 1;
                    }
                    break;
                case KING:
                    if (piece.color == BLACK) {
                        if (draw_sprite(bK, j * 108, i * 108)) return 1;
                    } else {
                        if (draw_sprite(wK, j * 108, i * 108)) return 1;
                    }
                    break;
                case EMPTY:
                    draw_sprite(wP, j * 108, i * 108);
                    break;
                
                default:
                    break;
            }
        }
    }

    return 0;
}








