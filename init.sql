CREATE TABLE IF NOT EXISTS food (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    calories INT NOT NULL,
    protein FLOAT NOT NULL
);

INSERT INTO food (name, calories, protein) VALUES
('Chicken Breast', 165, 31.0),
('Salmon', 208, 20.0),
('Egg', 155, 13.0);
