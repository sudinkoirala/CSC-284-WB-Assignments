#include <iostream>
#include <memory>
#include <string>
#include <utility>

class Document {
public:
    Document(const std::string& title_, const std::string& content_)
        : title(title_), content(std::make_unique<std::string>(content_)) {
        std::cout << "Document \"" << title << "\" created.\n";
    }
    ~Document() {
        std::cout << "Document \"" << title << "\" destroyed.\n";
    }
    void show() const {
        std::cout << "Title: " << title << "\n";
        std::cout << "Content: " << *content << "\n";
    }
    void edit(const std::string& newContent) { *content = newContent; }
private:
    std::string title;
    std::unique_ptr<std::string> content;
};

std::unique_ptr<Document> createDocument(const std::string& title, const std::string& content) {
    return std::make_unique<Document>(title, content);
}
std::shared_ptr<Document> createSharedDocument(const std::string& title, const std::string& content) {
    return std::make_shared<Document>(title, content);
}

int main() {
    using std::cout;
    using std::move;
    using std::shared_ptr;
    using std::unique_ptr;

    cout << "=== Unique_ptr demonstration ===\n";
    unique_ptr<Document> doc1 = createDocument("My Unique Doc", "Initial content");
    doc1->show();

    unique_ptr<Document> doc2 = move(doc1);
    if (!doc1) { cout << "doc1 no longer owns the document\n"; }
    doc2->edit("Updated content");
    doc2->show();

    cout << "\n=== Shared_ptr demonstration ===\n";
    shared_ptr<Document> sharedDoc = createSharedDocument("Shared Doc", "Shared content");
    {
        shared_ptr<Document> viewer = sharedDoc;
        viewer->show();
        viewer->edit("Edited by viewer");
    }
    sharedDoc->show();
    cout << "End of main()\n";
    return 0;
}

