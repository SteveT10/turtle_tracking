import express from "express";
const app = express();

app.get("/", (req, res) => {
    const headers = req.headers;
    res.status(200).send(headers);
});

app.listen(process.env.SERVER_PORT, (
) => {
    console.log(`Server is running on port ${process.env.SERVER_PORT}`);
});