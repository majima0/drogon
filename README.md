# ビルド
## dockerビルド
```
sudo docker build -t deepstream-drogon:latest -f ./docker/Dockerfile .
```

## 実行ファイルビルド
```
sudo docker run -it --rm --gpus all --net=host -v ${PWD}/sources:/workspace/project/sources -w /workspace/project/sources -p 8080:8080 deepstream-drogon
cd build
cmake ..
make
./javascript_coorperation
```

# アクセス
```
http://localhost:8080/uploadSample/
```
