// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "vulcan_00t.h"
#include "kaitai/exceptions.h"

vulcan_00t_t::vulcan_00t_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, vulcan_00t_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_root = nullptr;
    m_other_roots = nullptr;
    _read();
}

void vulcan_00t_t::_read() {
    m_signature = m__io->read_bytes(8);
    if (!(signature() == std::string("\xEA\xFB\xA7\x8A\x76\x75\x6C\x5A", 8))) {
        throw kaitai::validation_not_equal_error<std::string>(std::string("\xEA\xFB\xA7\x8A\x76\x75\x6C\x5A", 8), signature(), _io(), std::string("/seq/0"));
    }
    m_format = m__io->read_u4le();
    m_compression_style = static_cast<vulcan_00t_t::compression_style_t>(m__io->read_u4le());
    m_compression_level = m__io->read_u4le();
    m_compression_block_size = m__io->read_u4le();
    m_root = std::unique_ptr<root_t>(new root_t(m__io, this, m__root));
    n_other_roots = true;
    if (format() > 1) {
        n_other_roots = false;
        m_other_roots = std::unique_ptr<other_roots_t>(new other_roots_t(m__io, this, m__root));
    }
}

vulcan_00t_t::~vulcan_00t_t() {
    _clean_up();
}

void vulcan_00t_t::_clean_up() {
    if (!n_other_roots) {
    }
}

vulcan_00t_t::level1_pointer_t::level1_pointer_t(uint64_t p_index, kaitai::kstream* p__io, vulcan_00t_t::level0_pointer_t* p__parent, vulcan_00t_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_index = p_index;
    m_children = nullptr;
    f_children = false;
    _read();
}

void vulcan_00t_t::level1_pointer_t::_read() {
    m_disk_offset = m__io->read_u8le();
}

vulcan_00t_t::level1_pointer_t::~level1_pointer_t() {
    _clean_up();
}

void vulcan_00t_t::level1_pointer_t::_clean_up() {
    if (f_children && !n_children) {
    }
}

std::vector<std::unique_ptr<vulcan_00t_t::level2_pointer_t>>* vulcan_00t_t::level1_pointer_t::children() {
    if (f_children)
        return m_children.get();
    n_children = true;
    if (disk_offset() != 0) {
        n_children = false;
        std::streampos _pos = m__io->pos();
        m__io->seek(disk_offset());
        int l_children = 256;
        m_children = std::unique_ptr<std::vector<std::unique_ptr<level2_pointer_t>>>(new std::vector<std::unique_ptr<level2_pointer_t>>());
        m_children->reserve(l_children);
        for (int i = 0; i < l_children; i++) {
            m_children->push_back(std::move(std::unique_ptr<level2_pointer_t>(new level2_pointer_t(((index() * 256) + i), m__io, this, m__root))));
        }
        m__io->seek(_pos);
        f_children = true;
    }
    return m_children.get();
}

vulcan_00t_t::root_t::root_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, vulcan_00t_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_children = nullptr;
    f_children = false;
    _read();
}

void vulcan_00t_t::root_t::_read() {
    m_disk_offset = m__io->read_u8le();
    m_max_offset = m__io->read_u8le();
}

vulcan_00t_t::root_t::~root_t() {
    _clean_up();
}

void vulcan_00t_t::root_t::_clean_up() {
    if (f_children && !n_children) {
    }
}

std::vector<std::unique_ptr<vulcan_00t_t::level0_pointer_t>>* vulcan_00t_t::root_t::children() {
    if (f_children)
        return m_children.get();
    n_children = true;
    if (disk_offset() != 0) {
        n_children = false;
        std::streampos _pos = m__io->pos();
        m__io->seek(disk_offset());
        int l_children = 256;
        m_children = std::unique_ptr<std::vector<std::unique_ptr<level0_pointer_t>>>(new std::vector<std::unique_ptr<level0_pointer_t>>());
        m_children->reserve(l_children);
        for (int i = 0; i < l_children; i++) {
            m_children->push_back(std::move(std::unique_ptr<level0_pointer_t>(new level0_pointer_t(i, m__io, this, m__root))));
        }
        m__io->seek(_pos);
        f_children = true;
    }
    return m_children.get();
}

vulcan_00t_t::page_t::page_t(uint64_t p_page_index, kaitai::kstream* p__io, vulcan_00t_t::level3_pointer_t* p__parent, vulcan_00t_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_page_index = p_page_index;
    f_page_start = false;
    f_page_end = false;
    _read();
}

void vulcan_00t_t::page_t::_read() {
    m_compressed_data_size = m__io->read_u4le();
    m_disk_page_size = m__io->read_u4le();
    m_compressed_data = m__io->read_bytes(compressed_data_size());
}

vulcan_00t_t::page_t::~page_t() {
    _clean_up();
}

void vulcan_00t_t::page_t::_clean_up() {
}

int32_t vulcan_00t_t::page_t::page_start() {
    if (f_page_start)
        return m_page_start;
    m_page_start = (page_index() * _root()->compression_block_size());
    f_page_start = true;
    return m_page_start;
}

int32_t vulcan_00t_t::page_t::page_end() {
    if (f_page_end)
        return m_page_end;
    m_page_end = ((page_index() + 1) * _root()->compression_block_size());
    f_page_end = true;
    return m_page_end;
}

vulcan_00t_t::other_roots_t::other_roots_t(kaitai::kstream* p__io, vulcan_00t_t* p__parent, vulcan_00t_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_other_roots = nullptr;
    _read();
}

void vulcan_00t_t::other_roots_t::_read() {
    m_num_roots = m__io->read_u4le();
    int l_other_roots = (num_roots() - 1);
    m_other_roots = std::unique_ptr<std::vector<std::unique_ptr<root_t>>>(new std::vector<std::unique_ptr<root_t>>());
    m_other_roots->reserve(l_other_roots);
    for (int i = 0; i < l_other_roots; i++) {
        m_other_roots->push_back(std::move(std::unique_ptr<root_t>(new root_t(m__io, this, m__root))));
    }
}

vulcan_00t_t::other_roots_t::~other_roots_t() {
    _clean_up();
}

void vulcan_00t_t::other_roots_t::_clean_up() {
}

vulcan_00t_t::level0_pointer_t::level0_pointer_t(uint64_t p_index, kaitai::kstream* p__io, vulcan_00t_t::root_t* p__parent, vulcan_00t_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_index = p_index;
    m_children = nullptr;
    f_children = false;
    _read();
}

void vulcan_00t_t::level0_pointer_t::_read() {
    m_disk_offset = m__io->read_u8le();
}

vulcan_00t_t::level0_pointer_t::~level0_pointer_t() {
    _clean_up();
}

void vulcan_00t_t::level0_pointer_t::_clean_up() {
    if (f_children && !n_children) {
    }
}

std::vector<std::unique_ptr<vulcan_00t_t::level1_pointer_t>>* vulcan_00t_t::level0_pointer_t::children() {
    if (f_children)
        return m_children.get();
    n_children = true;
    if (disk_offset() != 0) {
        n_children = false;
        std::streampos _pos = m__io->pos();
        m__io->seek(disk_offset());
        int l_children = 256;
        m_children = std::unique_ptr<std::vector<std::unique_ptr<level1_pointer_t>>>(new std::vector<std::unique_ptr<level1_pointer_t>>());
        m_children->reserve(l_children);
        for (int i = 0; i < l_children; i++) {
            m_children->push_back(std::move(std::unique_ptr<level1_pointer_t>(new level1_pointer_t(((index() * 256) + i), m__io, this, m__root))));
        }
        m__io->seek(_pos);
        f_children = true;
    }
    return m_children.get();
}

vulcan_00t_t::level2_pointer_t::level2_pointer_t(uint64_t p_index, kaitai::kstream* p__io, vulcan_00t_t::level1_pointer_t* p__parent, vulcan_00t_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_index = p_index;
    m_children = nullptr;
    f_children = false;
    _read();
}

void vulcan_00t_t::level2_pointer_t::_read() {
    m_disk_offset = m__io->read_u8le();
}

vulcan_00t_t::level2_pointer_t::~level2_pointer_t() {
    _clean_up();
}

void vulcan_00t_t::level2_pointer_t::_clean_up() {
    if (f_children && !n_children) {
    }
}

std::vector<std::unique_ptr<vulcan_00t_t::level3_pointer_t>>* vulcan_00t_t::level2_pointer_t::children() {
    if (f_children)
        return m_children.get();
    n_children = true;
    if (disk_offset() != 0) {
        n_children = false;
        std::streampos _pos = m__io->pos();
        m__io->seek(disk_offset());
        int l_children = 256;
        m_children = std::unique_ptr<std::vector<std::unique_ptr<level3_pointer_t>>>(new std::vector<std::unique_ptr<level3_pointer_t>>());
        m_children->reserve(l_children);
        for (int i = 0; i < l_children; i++) {
            m_children->push_back(std::move(std::unique_ptr<level3_pointer_t>(new level3_pointer_t(((index() * 256) + i), m__io, this, m__root))));
        }
        m__io->seek(_pos);
        f_children = true;
    }
    return m_children.get();
}

vulcan_00t_t::level3_pointer_t::level3_pointer_t(uint64_t p_index, kaitai::kstream* p__io, vulcan_00t_t::level2_pointer_t* p__parent, vulcan_00t_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_index = p_index;
    m_page = nullptr;
    f_page = false;
    _read();
}

void vulcan_00t_t::level3_pointer_t::_read() {
    m_disk_offset = m__io->read_u8le();
}

vulcan_00t_t::level3_pointer_t::~level3_pointer_t() {
    _clean_up();
}

void vulcan_00t_t::level3_pointer_t::_clean_up() {
    if (f_page && !n_page) {
    }
}

vulcan_00t_t::page_t* vulcan_00t_t::level3_pointer_t::page() {
    if (f_page)
        return m_page.get();
    n_page = true;
    if (disk_offset() != 0) {
        n_page = false;
        std::streampos _pos = m__io->pos();
        m__io->seek(disk_offset());
        m_page = std::unique_ptr<page_t>(new page_t(index(), m__io, this, m__root));
        m__io->seek(_pos);
        f_page = true;
    }
    return m_page.get();
}
