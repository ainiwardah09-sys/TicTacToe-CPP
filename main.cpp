#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>

class TicTacToe : public QWidget
{
public:
    QPushButton *cells[9];
    QString board[9];
    QString player = "X";
    QLabel *status;
    bool gameOver = false;

    TicTacToe()
    {
        setWindowTitle("Tic-Tac-Toe");
        resize(360, 520);
        setMinimumSize(320, 450);

        QVBoxLayout *mainLayout = new QVBoxLayout(this);

        QLabel *title = new QLabel("TIC TAC TOE");
        title->setAlignment(Qt::AlignCenter);
        title->setStyleSheet(
            "font-size: 26px; font-weight: bold; color: #9B87F5;"
            );

        status = new QLabel("Giliran pemain X");
        status->setAlignment(Qt::AlignCenter);
        status->setStyleSheet(
            "font-size: 18px; color: white; padding: 10px;"
            );

        QGridLayout *grid = new QGridLayout();

        for (int i = 0; i < 9; i++) {
            board[i] = "";

            cells[i] = new QPushButton("");
            cells[i]->setMinimumSize(70, 70);
            cells[i]->setStyleSheet(
                "font-size: 32px; font-weight: bold;"
                "background-color: #222438;"
                "color: #B9A3FF;"
                "border-radius: 12px;"
                );

            grid->addWidget(cells[i], i / 3, i % 3);

            connect(cells[i], &QPushButton::clicked,
                    this, [this, i]() {
                        makeMove(i);
                    });
        }

        QPushButton *resetButton =
            new QPushButton("Main Lagi");

        resetButton->setMinimumHeight(45);
        resetButton->setStyleSheet(
            "font-size: 17px; color: white;"
            "background-color: #6C55D9;"
            "border-radius: 10px;"
            );

        connect(resetButton, &QPushButton::clicked,
                this, [this]() {
                    resetGame();
                });

        mainLayout->addWidget(title);
        mainLayout->addWidget(status);
        mainLayout->addLayout(grid);
        mainLayout->addWidget(resetButton);

        setStyleSheet("background-color: #10111A;");
    }

    void makeMove(int index)
    {
        if (gameOver || board[index] != "")
            return;

        board[index] = player;
        cells[index]->setText(player);

        if (checkWin()) {
            status->setText(player + " menang!");
            gameOver = true;
            return;
        }

        bool draw = true;

        for (int i = 0; i < 9; i++) {
            if (board[i] == "") {
                draw = false;
                break;
            }
        }

        if (draw) {
            status->setText("Permainan seri!");
            gameOver = true;
            return;
        }

        player = (player == "X") ? "O" : "X";
        status->setText("Giliran pemain " + player);
    }

    bool checkWin()
    {
        int wins[8][3] = {
            {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
            {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
            {0, 4, 8}, {2, 4, 6}
        };

        for (int i = 0; i < 8; i++) {
            int a = wins[i][0];
            int b = wins[i][1];
            int c = wins[i][2];

            if (board[a] != "" &&
                board[a] == board[b] &&
                board[b] == board[c]) {
                return true;
            }
        }

        return false;
    }

    void resetGame()
    {
        for (int i = 0; i < 9; i++) {
            board[i] = "";
            cells[i]->setText("");
        }

        player = "X";
        gameOver = false;
        status->setText("Giliran pemain X");
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    TicTacToe game;
    game.show();

    return app.exec();
}