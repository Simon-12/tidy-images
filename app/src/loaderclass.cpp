#include "loaderclass.h"

LoaderClass::LoaderClass(int buffer, QObject *parent) : QObject(parent) { m_bufferSize = buffer; }

void LoaderClass::initLoader(AppMode mode) {
    m_mode = mode;
    switch (m_mode) {
        case AppMode::Empty:
        case AppMode::Gallery:
        case AppMode::Video:
            m_text = "Load Files";
            break;
        case AppMode::Database:
            m_text = "Load Database";
            break;
        case AppMode::Image:
        case AppMode::Compare:
            m_text = "Load Images";
            break;
    }

    emit textChanged();
    setDialog(true);
}

void LoaderClass::startLoading(int size) {
    if (size == 0) {
        setDialog(false);
        return;
    }
    if (m_mode == AppMode::Empty) {
        setDialog(false);
        return;
    }
    setDialog(true);

    // Fill files
    m_files.clear();
    for (int i = 0; i < size; i++) m_files << i;

    // Fill images
    m_images.clear();
    if (m_mode == AppMode::Image || m_mode == AppMode::Compare) {
        int buffer = size < m_bufferSize ? size : m_bufferSize;
        for (int i = 0; i < buffer; i++) {
            m_images << i;
            if (m_mode == AppMode::Compare) m_images << i;  // Add second time
        }
    }

    m_size = m_files.size() + m_images.size();
    emit sizeChanged();
}

void LoaderClass::loadFile(int index) {
    // Check for index
    if (m_files.removeOne(index)) setProgress(m_progress += 1);

    if (!m_files.isEmpty()) return;
    if (m_images.isEmpty()) setDialog(false);
}

void LoaderClass::loadImage(int index) {
    if (!m_open) return;

    // Check for index
    if (m_images.removeOne(index)) setProgress(m_progress += 1);

    if (m_images.isEmpty()) setDialog(false);
}

void LoaderClass::singleStep() {
    // Emit single step
    setStep(m_step += 1);
}

void LoaderClass::setDialog(bool open) {
    // Refresh progresss and open or close dialog
    setProgress(0);
    m_size = -1;
    emit sizeChanged();
    m_open = open;
    emit openChanged();
}

void LoaderClass::setProgress(int progress) {
    m_progress = progress;
    emit progressChanged();
}

void LoaderClass::setStep(int step) {
    m_step = step;
    emit stepChanged();
}
