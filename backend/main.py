from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
import uvicorn

app = FastAPI()

app.add_middleware(CORSMiddleware, allow_origins=["*"], allow_methods=["*"], allow_headers=["*"])

@app.get("/table")
def get_table():
    return [
        {"name": "Alice", "age": 3},
        {"name": "Bob", "age": 25}
    ]

if __name__ == "__main__":
    uvicorn.run("main:app", host="127.0.0.1", port=8000)
