#include <iostream>
#include <memory>
#include <string>
#include <utility>

// Document class represents a text document with a title and content
class Document {
public:
    // Constructor: create a document with given title and content
    Document(const std::string& title_, const std::string& content_)
        : title(title_), content(std::make_unique<std::string>(content_)) {
        std::cout << "Document \"" << title << "\" created.\n";
    }

    // Destructor: called automatically when object is destroyed
    ~Document() {
        std::cout << "Document \"" << title << "\" destroyed.\n";
    }

    // Display the document's title and content
    void show() const {
        std::cout << "Title: " << title << "\n";
        std::cout << "Content: " << *content << "\n";
    }

    // Edit the content of the document
    void edit(const std::string& newContent) { *content = newContent; }

private:
    std::string title;                          // document title
    std::unique_ptr<std::string> content;       // smart pointer to content
};

// Create a unique_ptr Document
std::unique_ptr<Document> createDocument(const std::string& title, const std::string& content) {
    return std::make_unique<Document>(title, content);
}

// Create a shared_ptr Document
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

    // Transfer ownership from doc1 to doc2
    unique_ptr<Document> doc2 = move(doc1);
    if (!doc1) { cout << "doc1 no longer owns the document\n"; }
    doc2->edit("Updated content");
    doc2->show();

    cout << "\n=== Shared_ptr demonstration ===\n";
    shared_ptr<Document> sharedDoc = createSharedDocument("Shared Doc", "Shared content");
    {
        // viewer is a second owner of the shared document
        shared_ptr<Document> viewer = sharedDoc;
        viewer->show();
        viewer->edit("Edited by viewer");
    } // viewer goes out of scope, but sharedDoc still keeps the object alive

    sharedDoc->show();
    cout << "End of main()\n";
    return 0;
}
