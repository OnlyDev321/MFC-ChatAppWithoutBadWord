# 💬 MFC-ChatAppWithoutBadWord

## 📚 Project Resources

Additional project materials, reports, screenshots, and related documents can be found in the Google Drive folder below:

🔗 https://drive.google.com/drive/folders/17WrUJRhqYbrOry2TyuDJX__mBL_UgvZc?usp=sharing

The folder includes supporting resources used throughout the development and evaluation of the MFC-ChatAppWithoutBadWord project, such as project reports, presentation materials, implementation documents, and demonstration assets.

## 📌 Project Overview

MFC-ChatAppWithoutBadWord is a real-time online chat application developed using Microsoft Foundation Classes (MFC). The system provides personalized prohibited-word filtering, allowing each user to manage their own blacklist of inappropriate words.

Whenever a message is sent, the application automatically detects and replaces prohibited words based on the recipient's custom filtering settings. Through flexible user-specific moderation and real-time message processing, this project aims to create a safer and more positive communication environment.

This project proposes a **Personalized Prohibited Word Filtering System** that enables users to:

- Create their own prohibited-word lists
- Apply customized filtering rules individually
- Detect prohibited words in real time
- Automatically replace prohibited words with `*`
- Maintain independent filtering settings for each user

---

## ✨ Key Features

- 💬 Real-time online chatting between users.
- 🚫 Personalized prohibited-word filtering.
- 📝 User-managed custom blacklist.
- 🔄 Automatic detection and replacement of inappropriate words.
- ⚡ Real-time message processing.
- 🔐 Improved communication safety and user experience.

---

## 🛠️ Technologies Used

- Language: C++
- Framework: Microsoft Foundation Classes (MFC)
- Networking: Windows Socket Programming (Winsock)
- Development Environment: Microsoft Visual Studio

---

### 💬 Real-Time Chat

- Instant message transmission
- Multi-client communication
- Low-latency message processing

### 🔍 Real-Time Filtering

- Detect prohibited words immediately
- Filter messages before displaying them
- Replace detected words with asterisks (`*`)

#### Example

**Original Message**

```text
You are stupid
```

**Filtered Message**

```text
You are ******
```

---

## 🏗️ System Architecture

```text
+-------------+
|   Client A  |
+-------------+
       |
       |
       v
+------------------+
|     Chat Server  |
+------------------+
       ^
       |
       |
+-------------+
|   Client B  |
+-------------+
```

### Processing Flow

1. User inputs a message.
2. The message is sent to the server.
3. The server delivers the message.
4. The client checks the message against its personal prohibited-word list.
5. Detected words are replaced with `*`.
6. The filtered message is displayed to the user.

---

## ⚙️ Filtering Mechanism

The project adopts a **dictionary-based filtering approach**.

### Advantages

- Simple implementation
- Fast processing speed
- Suitable for real-time systems
- Easy customization

### Limitation

- Difficult to detect newly created slang or modified offensive words

Examples:

```text
badword
```

can be detected, but variants such as

```text
b@dword
b a d w o r d
```

may require additional processing rules.

---

# 🔄 Workflow

```text
User Message
      |
      v
Receive Message
      |
      v
Compare with Personal
Prohibited Word List
      |
      v
Word Detected?
   /      \
 Yes      No
  |         |
  v         v
Replace    Display
with *     Original
  |
  v
Display
```

---

## 🧪 Experiment

### Test Environment

- Chat Server
- Two Chat Clients
- Chat Dataset
- Prohibited Word Dataset

### Procedure

1. Start the chat server.
2. Connect two clients.
3. Exchange messages without filtering.
4. Add prohibited words to each client.
5. Repeat chatting.
6. Verify filtering behavior.
7. Compare filtering results across different users.

---

## 📊 Results

The experiments showed that:

✅ Prohibited words were successfully detected.

✅ Messages containing prohibited words were correctly filtered.

✅ Different users could maintain different prohibited-word lists.

✅ The same message could be displayed differently depending on each user's settings.

✅ Real-time performance was maintained without noticeable delay.

---

## 🚀 Future Improvements

The current implementation uses a dictionary-based filtering approach.

Future work may include:

- Deep Learning-based profanity detection
- Context-aware filtering
- NLP-based offensive language analysis
- Detection of modified or obfuscated words
- Dynamic filtering using neural networks
- Multi-language support

---

## 🎯 Expected Benefits

- Improve online communication quality
- Reduce exposure to offensive language
- Provide personalized user experiences
- Support safer online communities
- Enhance user satisfaction

---

## 👨‍💻 Authors

**Soongsil University – School of Software**

- Dong-hwan Kim
- Youn-hyeong Nam
- Seung-hwan Boo
- Jun-seok Jang
- Hae-yoon Jeong
- Tran Trung Hau

---

## 📄 License

This project was developed for educational and research purposes.

> 본 프로젝트는 황우섭 교수님의 「윈도우프로그래밍및실습」 수업의 일환으로 수행되었습니다.
