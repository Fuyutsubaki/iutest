//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_ver.hpp
 * @brief		iris unit test version ��` �t�@�C��
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2011-2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_ver_HPP_D65CB7A7_D2AD_40fe_8F5F_8FBF376A0010_
#define INCG_IRIS_iutest_ver_HPP_D65CB7A7_D2AD_40fe_8F5F_8FBF376A0010_

//======================================================================
// include

//======================================================================
// define
#define	IUTEST_VER			0x01069919u	//!< iutest version 1.6.99.19
#define IUTEST_MAJORVER		0x01u		//!< Major Version
#define IUTEST_MINORVER		0x06u		//!< Minor Version
#define IUTEST_BUILD		0x99u		//!< Build
#define IUTEST_REVISION		0x19u		//!< Revision

/**
 * @mainpage
 * @sa	@b	ProjectHome \n
 *			sourceforge : http://sourceforge.jp/projects/iutest/ \n
 *			github      : https://github.com/srz-zumix/iutest \n
 *
 * @par		copyright
 * Copyright (C) 2011-2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 *
 * @par		LICENSE

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:\n
\n
  1. Redistributions of source code must retain the above copyright notice,\n
     this list of conditions and the following disclaimer.\n
  2. Redistributions in binary form must reproduce the above copyright notice,\n
     this list of conditions and the following disclaimer in the documentation \n
     and/or other materials provided with the distribution.\n
  3. the copyright holder's name is not used to endorse products \n
     built using this software without specific written permission.\n
\n
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

/**
 * @page	CMDLINE		�R�}���h���C���I�v�V����
 * @par		Command Line Options
 <table>
   <tr><td>--help, -h                        </td><td></td><td>generate help message.</td></tr>
   <tr><td>--iutest_output                   </td><td>xml[:path]</td><td>path of xml report.</td></tr>
   <tr><td>--iutest_list_tests               </td><td></td><td>list up tests.</td></tr>
   <tr><td>--iutest_list_tests_with_where    </td><td></td><td>list up tests with where.</td></tr>
   <tr><td>--iutest_color                    </td><td>&lt;yes|no|auto|ansi&gt;</td><td>console color enable.</td></tr>
   <tr><td>--iutest_filter                   </td><td>&lt;filter&gt;</td><td>Select the test run.</td></tr>
   <tr><td>--iutest_shuffle                  </td><td></td><td>do shuffle test.</td></tr>
   <tr><td>--iutest_random_seed              </td><td>&lt;seed&gt;</td><td>set random seed.</td></tr>
   <tr><td>--iutest_also_run_disabled_tests  </td><td></td><td>run disabled tests.</td></tr>
   <tr><td>--iutest_break_on_failure         </td><td>[0|1]</td><td>When that failed to break.</td></tr>
   <tr><td>--iutest_throw_on_failure         </td><td>[0|1]</td><td>When that failed to throw.</td></tr>
   <tr><td>--iutest_catch_exceptions         </td><td>&lt;0|1&gt;</td><td>catch exceptions enable.</td></tr>
   <tr><td>--iutest_print_time               </td><td>&lt;0|1&gt;</td><td>Setting the display of elapsed time.</td></tr>
   <tr><td>--iutest_repeat                   </td><td>&lt;count&gt;</td><td>Set the number of repetitions of the test.</td></tr>
   <tr><td>--iutest_stream_result_to         </td><td>&lt;host:port&gt;</td><td>Set stream test results server.</td></tr>
   <tr><td>--iutest_file_location            </td><td>&lt;auto|vs|gcc&gt;</td><td>Format file location messages.</td></tr>
   <tr><td>--feature                         </td><td></td><td>show iutest feature.</td></tr>
   <tr><td>--version, -v                     </td><td></td><td>show iutest version.</td></tr>
 </table>
  * yes or no option can use "yes|y|on|true|t|1|no|n|off|false|f|0"
*/

/**
 * @page	CHANGELOG		�ύX����
 * @par		Changes
 <ul>
  <li>v1.6.99.19
    <ul>
      <li>�e�X�g�t�B�N�X�`���̒�`���Ȃ���l�̃p�����[�^���e�X�g��ǉ�(IUTEST_AP,IUTEST_INSTANTIATE_TEST_CASE_AP)</li>
      <li>�l�̃p�����[�^�� operator + �ŘA���ł���悤�ɏC��</li>
      <li>�l�̃p�����[�^��A������ ::iutest::Concat ��ǉ�</li>
      <li>IUTEST_TYPED_TEST,IUTEST_TYPED_TEST_P �̕ʖ��}�N����ǉ�(IUTEST_T, IUTEST_TP)</li>
      <li>xml �o�͂� timestamp ��ǉ�</li>
      <li>�O������̌��ؗp�}�N�� IUTEST_ASSUME_* ��ǉ�</li>
      <li>SSTP �ʒm���X�i�[��ǉ�</li>
      <li>Windows �������j���[�o�^���[�e�B���e�B��ǉ�</li>
      <li>�l�̃p�����[�^���e�X�g�����{��e�X�g���ɑΉ����Ă��Ȃ����������C��</li>
      <li>�r���h�G���[�C��</li>
    </ul>
  </li>
  <li>v1.6.1.0
    <ul>
      <li>Visual Studio 2013 Preview �Ή�</li>
    </ul>
  </li>
  <li>v1.6.0.0
    <ul>
      <li>stream result �Ή�</li>
      <li>gtest ���[�h�� AssertionReturn ���g����悤�ɑΉ�</li>
      <li>AssertionReturn �̎d�l�ύX</li>
      <li>::iutest::RandomGenerator ��ǉ�</li>
      <li>::iutest::RandomValues �ŗ����V�[�h���w��ł���悤�ɏC��</li>
      <li>spi �� TestPartResult �����`�F�b�N����悤�ɕύX</li>
      <li>spi �� substr �Ń��b�Z�[�W���`�F�b�N����悤�ɕύX</li>
	  <li>ASSERT_*, EXPECT_*, INFORM_* �}�N���̃X�g���[���� iomanip ���g�p�ł��Ȃ����������C��</li>
    </ul>
  </li>
  <li>v1.5.0.4
    <ul>
      <li>--iutest_filter �Ń}�b�`���Ȃ������e�X�g�� XML �ɏo�͂��Ȃ��悤�ɕύX</li>
      <li>XML �o�͂� skipped �Ƀ��b�Z�[�W���o�͂���悤�ɏC��</li>
      <li>--iutest_filter �Ƀ}�b�`�����e�X�g�����擾�ł���悤�ɏC��</li>
      <li>�f�t�H���g���O�o�͂� --iutest_filter �̌��ʂ��l�������o�͂ɕύX</li>
    </ul>
  </li>
  <li>v1.5.0.0
    <ul>
      <li>���{��e�X�g���ɑΉ�</li>
      <li>SetUpTestCase �Ȃǂ̃e�X�g���s���ȊO�ł� RecordProperty �ł���悤�ɕύX</li>
      <li>iutest_list_tests_with_where �R�}���h���C���I�v�V������ǉ�</li>
      <li>IUTEST_TYPED_TEST_CASE,IUTEST_TYPED_TEST_CASE_P �ɒ��� ::iutest::Types ��������悤�ɏC��/li>
      <li>������g�����������ꍇ�ɃG���[���o�͂���悤�ɏC��</li>
      <li>IUTEST_PEEP �̎d�l�ύX</li>
      <li>MiniDump �o�͂ɑΉ�</li>
      <li>noexcept �ɑΉ�</li>
    </ul>
  </li>
  <li>v1.4.0.0
    <ul>
      <li>IUTEST_ASSERT_* �� void �ȊO�̖߂�l��Ԃ���悤�ɏC��(::iutest::AssertionReturn)</li>
      <li>::iutest::Types �����o�[�Ɍ^���擾���� get ��ǉ�</li>
      <li>::iutest::ValuesIn �� initializer_list �ɑΉ�</li>
      <li>�l�̃p�����[�^���e�X�g�����ɔC�ӂ̃p�����[�^�𐶐����� ValuesGen ��ǉ�</li>
      <li>�l�̃p�����[�^���e�X�g�����ɗ����p�����[�^�𐶐����� RandomValues ��ǉ�</li>
      <li>extern template �Ή�</li>
      <li>C++11 random �w�b�_�[���g�p�ł���Ƃ� distribution ���g���悤�ɕύX</li>
      <li>�R�[�h���̓c�[���̂��߂̃R�[�h�̒ǉ����(__analysis_assume) �� IUTEST_*_NULL �� IUTEST_*_NOTNULL �ɒǉ�(MSVC)</li>
	  <li>�Â��R���p�C���ւ̑Ή�</li>
    </ul>
  </li>
  <li>v1.3.1.0
    <ul>
      <li>IUTEST_SKIP �����Ƃ��̃��O��ǉ�</li>
      <li>IUTEST_SKIP() << "message" �ɑΉ�</li>
      <li>�X�L�b�v�����e�X�g�̃��O�o�͂��C��</li>
      <li>�R���p�C���̒ʂ�Ȃ��e�X�g�R�[�h��������e�X�g�����}�N��(*_IGNORE)��ǉ�</li>
    </ul>
  </li>
  <li>v1.3.0.1
    <ul>
      <li>IUTEST_THROW_ON_ASSERT_FAILURE �� IUTEST_USE_THROW_ON_ASSERT_FAILURE �ɕύX</li>
      <li>IUTEST_FRIEND_TYPED_TEST ��ǉ�</li>
      <li>�����V�[�h���J��Ԃ����ɕK���ς��悤�ɏC��</li>
      <li>GTEST �Ŏn�܂���ϐ��ɑΉ�</li>
      <li>���b�Z�[�W�o�͂̃t�@�C��/�s�̃t�H�[�}�b�g�𓮓I�ɕύX�ł���I�v�V������ǉ�(--iutest_file_location)</li>
      <li>gtest ���[�h�ł̃r���h�G���[�C��</li>
      <li>IUTEST_*_FATAL_FAILURE, IUTEST_*_NONFATAL_FAILURE �� lambda �𗘗p���ĕϐ��ɃA�N�Z�X�ł���悤�ɏC��</li>
      <li>IUTEST_*_NO_FATAL_FAILURE �� FATAL FAILURE �݂̂Ŕ��f����悤�ɕύX</li>
      <li>IUTEST_*_NO_FAILURE ��ǉ�</li>
      <li>���C�u�����r���h�Ή�</li>
      <li>CUDA �Ή�</li>
      <li>explicit conversion operator �Ή�</li>
    </ul>
  </li>
  <li>v1.2.0.2
    <ul>
      <li>IUTEST_*_EQ_COLLECTIONS �A�T�[�V������ǉ�</li>
      <li>Android NDK �Ή�</li>
      <li>���O��Ԃ�񋟂��� IUTEST_PACKAGE �ǉ�</li>
      <li>IUTEST_*_STRNE, IUTEST_*_STRCASENE �̎��s���b�Z�[�W�����P</li>
      <li>�v���O���X�o�̓��X�i�[��ǉ�</li>
    </ul>
  </li>
  <li>v1.1.2.0
    <ul>
      <li>IUTEST_*_NO_THROW �Ŏ��s�����Ƃ��ɗ�O�̏����o�͂���悤�ɏC��</li>
      <li>printer �C��</li>
    </ul>
  </li>
  <li>v1.1.1.2
    <ul>
      <li>Windows Mobile �ł̃r���h�G���[�C��</li>
      <li>IUTEST_HAS_STRINGSTREAM=0 �̂Ƃ��̃r���h�G���[�C��</li>
      <li>�錾�ƒ�`�𕪗�</li>
    </ul>
  </li>
  <li>v1.1.0.0
    <ul>
      <li>v1.1.0 �����[�X�o�[�W����</li>
    </ul>
  </li>
  <li>v1.0.7.1
    <ul>
      <li>2�o�C�g������ xml �ɐ������o�͂���Ȃ������C���isetlocale ���K�v�j</li>
      <li>��O�̒l����������q��A�T�[�V������ IUTEST_*_THROW_PRED_FORMAT2 �ǉ�</li>
      <li>��O�̒l����������A�T�[�V�����̃��O�o�͂��C��</li>
    </ul>
  </li>
  <li>v1.0.6.0
    <ul>
      <li>��O�̒l����������A�T�[�V������ EQ/NE/STREQ/STRCASEEQ �ɏC��</li>
    </ul>
  </li>
  <li>v1.0.5.2
    <ul>
      <li>�����I�ȃX�L�b�v�Ƃ��� IUTEST_SKIP ��ǉ�</li>
      <li>�R���\�[���o�͐�𓮓I�ɕύX�ł���悤�ɏC��</li>
      <li>���s���ׂ��e�X�g�����s����Ȃ������ꍇ�Ɏ��s���o�͂���悤�ɏC��</li>
      <li>Visual Studio UnitTest Framework �� IUTEST_P,IUTEST_TYPED_TEST,IUTEST_TYPED_TEST_P ���g�p�ł���悤�ɏC��(tr1)</li>
    </ul>
  </li>
  <li>v1.0.4.0
    <ul>
      <li>iutest::Pairwise ��ǉ�</li>
      <li>�R�[�h�T�C�Y�팸</li>
    </ul>
  </li>
  <li>v1.0.3.1
    <ul>
      <li>�t�@�C���p�X����⏕�N���X�̒ǉ�</li>
      <li>IUTEST_*_EQ �� if( expected == actual ) ���� if( actual == expected ) �ɕύX</li>
      <li>IUTEST_*_NO_FATAL_FAILURE �ɋ�� statement ��^���Ă��x�����o�Ȃ��悤�ɏC��</li>
    </ul>
  </li>
  <li>v1.0.2.0
    <ul>
      <li>��O�̒l����������A�T�[�V������ǉ�</li>
    </ul>
  </li>
  <li>v1.0.1.0
    <ul>
      <li>CRT �Z�L�����e�B�����֐��̎��s���n���h���ɑΉ�</li>
      <li>iutest::InitIrisUnitTest ���Ă΂�Ă��Ȃ��ꍇ�Ɍx�����o���悤�ɕύX</li>
    </ul>
  </li>
  <li>v1.0.0.0
    <ul>
      <li>���������[�X</li>
    </ul>
  </li>
  <li>v0.36.2.1
    <ul>
      <li>�^���\�L���f�}���O������悤�ɏC��</li>
      <li>Google Test ���g�p�����ꍇ�ł� std::string �ɑΉ������������r�A�T�[�V�������g����悤�ɏC��</li>
      <li>Google Test ���g�p�������� wchar_t �ł� STRCASENE ���g����悤�ɏC��</li>
      <li>IUTEST_THROW_ON_ASSERT_FAILURE �̃f�t�H���g�l�� 0 �ɕύX</li>
      <li>IUTEST_THROW_ON_ASSERT_FAILURE ���L���ȂƂ� IUTEST_*_FATAL_FAILURE �����������삵�Ȃ������C��</li>
      <li>spi �e�X�g���� break_on_failure/throw_on_failure �Ŏ~�܂�Ȃ��悤�ɏC��</li>
      <li>�A�T�[�V�����݂̗̂��p���ł���悤�ɏC��</li>
      <li>�O���[�o���X�R�[�v�������Z�q������悤�ɏC��</li>
      <li>Google Test �̃o�[�W�������ʂ�ǉ�</li>
    </ul>
  </li>
  <li>v0.35.0.0
    <ul>
      <li>IUTEST_PMZ, IUTEST_PMZ_F �e�X�g�����}�N����ǉ�</li>
    </ul>
  </li>
  <li>v0.34.0.0
    <ul>
      <li>���� IUTEST_REGISTER_TYPED_TEST_CASE_P �ł��Ȃ��s����C��</li>
      <li>�e�X�g�����f�����ۂɎ��s����Ȃ������e�X�g�� notrun �� XML �o�͂���悤�ɏC��</li>
      <li>--iutest_break_on_failure ��L���ɂ��f�o�b�O�Ȃ����s�������Ƃ��Ƀ_�C�A���O���łȂ��悤�ɏC��</li>
    </ul>
  </li>
  <li>v0.33.1.0
    <ul>
      <li>iutest::UnitTest::repeat_counter �֐���ǉ�</li>
      <li>OnTestIterationStart/End �� iteration ������ 0 ����n�܂�悤�ɏC��</li>
      <li>QuietResultPrinter �ǉ�</li>
      <li>util �C��</li>
    </ul>
  </li>
  <li>v0.32.0.0
    <ul>
      <li>iutest::Combine ���ϒ��ɑΉ�</li>
      <li>IUTEST_PEEP �� cv �C�����ꂽ�����o�ɑΉ�</li>
      <li>�e�X�g�S�́A�e�X�g�P�[�X�̌o�ߎ��Ԃ̌v�����@��ύX</li>
    </ul>
  </li>
  <li>v0.31.2.1
    <ul>
      <li>IUTEST_STATIC_ASSERT �ǉ�</li>
      <li>IUTEST_SCOPED_TRACE �� gtest �Ɠ����L�@���g����悤�ɏC��</li>
      <li>std::chrono::high_resolution_clock �ɑΉ�</li>
      <li>iutest::PrintToString �ŃX�g���[���o�͂ł��Ȃ��^�ɑΉ��i�o�C�g�z����o�́j</li>
      <li>�e�X�g�p�����̃V�[�h�擾��ǉ�</li>
      <li>IUTEST_*_TRUE|FALSE �� iutest::AssertionResult ���󂯎���悤�ɏC��</li>
      <li>--feature �I�v�V������ǉ�</li>
    </ul>
  </li>
  <li>v0.30.1.0
    <ul>
      <li>IUTEST_*_STREQ, IUTEST_*_STRNE �� char16_t, char32_t �ɑΉ�</li>
      <li>�ꕔ�̊��Ń��C�h������� IUTEST_*_STRCASEEQ, IUTEST_*_STRCASENE ���啶������������ʂ���Ă����s����C��</li>
      <li>nullptr �ɑΉ�</li>
      <li>�����V�[�h���w�肵�Ȃ������ꍇ�Ɍ��ݎ����i�~���b�j����V�[�h�����肷��悤�ɏC��</li>
      <li>�V���b�t���e�X�g���ɗ����V�[�h�����O�o�͂���悤�ɏC��</li>
      <li>�����擾�p�̃R���t�B�O�}�N����ǉ�</li>
      <li>iutest::PrintToString �ŃR���p�C�����ʂ�Ȃ��^���������̂ŏC��</li>
      <li>EQ�n�A�T�[�V�����̃��b�Z�[�W���C��</li>
    </ul>
  </li>
  <li>v0.29.1.0
    <ul>
      <li>IUTEST_INSTANTIATE_TYPED_TEST_CASE_P �̌^���X�g�ɒP��̌^(int, char...)���g�p�ł���悤�ɏC��</li>
      <li>ASSERT �}�N������O�� throw ���邩�ݒ肷�� IUTEST_THROW_ON_ASSERT_FAILURE ��ǉ�(default=1) </li>
      <li>--iutest_throw_on_failure ���ɒv���I�ł͂Ȃ��G���[�Ŏ��s�����ꍇ throw ����Ȃ��s����C��</li>
      <li>2�� IUTEST_RUN_ALL_TESTS �����Ƃ��̕s����C��</li>
      <li>Environment �̉���^�C�~���O���C��</li>
    </ul>
  </li>
  <li>v0.28.0.1
    <ul>
      <li>iutest::Environment::SetUp �Ȃǃe�X�g�ȊO�̏ꏊ�Ŏ��s�����ꍇ�ɑΉ�</li>
    </ul>
  </li>
  <li>v0.27.0.0
    <ul>
      <li>namespace ���l������ IUTEST_MAKE_SCOPED_PEEP, IUTEST_SCOPED_PEEP �}�N����ǉ�</li>
      <li>iutest::AddGlobalTestEnvironment ���g���ƃR���p�C���G���[�ɂȂ�����C��</li>
      <li>iutest::Environment �� new ���Ďg���悤�Ɏd�l�ύX</li>
      <li>iutest::Environment �� TearDown �̎��s������ SetUp �̋t���ɕύX</li>
    </ul>
  </li>
  <li>v0.26.2.0
    <ul>
      <li>RecordProperty �ŃL�[���d�������ꍇ�ɏ㏑������悤�ɏC��</li>
      <li>IUTEST_HAS_PEEP, IUTEST_HAS_PEEP_FUNC, IUTEST_PEEP_STATIC_FUNC �R���t�B�O�}�N����ǉ�</li>
      <li>iutest_prod.hpp �� private �����o�[�ւ̃A�N�Z�X�@�\��ǉ�(IUTEST_MAKE_PEEP, IUTEST_PEEP_GET etc...)</li>
      <li>IUTEST_FRIEND_TEST �s��C��</li>
    </ul>
  </li>
  <li>v0.25.2.0
    <ul>
      <li>gtest �Ƃ̌݊������Ƃ�Ă��Ȃ������ӏ����C��</li>
      <li>IUTEST_FLAG �� filter ��ǉ�</li>
      <li>�I�v�V�����ɑΉ����ĂȂ��l���w�肵���Ƃ��Ƀw���v���o�͂���悤�ɏC��</li>
      <li>�^�U�l���w�肷��R�}���h���C���I�v�V������ yes|no �ɑΉ�</li>
      <li>xml �o�͂� type param, value param ���o�͂���悤�ɏC��</li>
      <li>RTTI ���L���ȂƂ��Ɍ^��񂪏o�͂���Ă��Ȃ����������C��</li>
      <li>PrintTo �� tuple �ɑΉ�</li>
    </ul>
  </li>
  <li>v0.24.1.0
    <ul>
      <li>Test Anything Protocol �t�@�C���o�̓��X�i�[��ǉ�</li>
      <li>DISABLE �e�X�g�� xml �� run �Ƃ��ďo�͂��������C��</li>
      <li>DISABLE �e�X�g�֌W�̕s����C��</li>
      <li>IUTEST_REPORT_SKIPPED �}�N���Ńf�t�H���gxml�o�̓��X�i�[�� skip ���o�͂��邩�I���ł���悤�ɏC��</li>
      <li>0|1 �̃t���O��n���I�v�V������ yes|no, y|n, true|false, t|f ���g����悤�ɏC��</li>
      <li>--iutest_color �� ANSI �I�v�V������ǉ��i�G�X�P�[�v�V�[�P���X�ŐF���o�́j</li>
      <li>--iutest_color �ő啶������������ʂ��Ȃ��悤�ɏC��</li>
    </ul>
  </li>
  <li>v0.23.3.0
    <ul>
      <li>IUTEST_*_SAME �A�T�[�V������ǉ�</li>
      <li>IUTEST_*_NULL, IUTEST_*_NOTNULL �A�T�[�V������ǉ�</li>
      <li>Test Anyting Protocol ���X�i�[�̒ǉ�</li>
      <li>�f�t�H���g���X�i�[����������Ƃ��� NULL �Q�Ƃ���s����C��</li>
      <li>�e�X�g���[�e�B���e�B�̃e�X�g�p�� iutest_spi.hpp ��ǉ�</li>
      <li>IUTEST_*_STR* �A�T�[�V������ NULL ��^���Ď��s������Ɨ���������C��</li>
      <li>--iutest_throw_on_failure=1 �Ńe�X�g�S�̂𒆒f����悤�ɕύX</li>
    </ul>
  </li>
  <li>v0.22.0.1
    <ul>
      <li>Variadic Templates �Ή��iiutest::Types, iutest::Values�j</li>
      <li>Variadic Templates �ɑΉ������q��A�T�[�V������ǉ��iIUTEST_*_PRED�j</li>
      <li>IUTEST_*_PRED_FORMAT ��ǉ�</li>
      <li>--iutest_throw_on_failure=1 �Ƃ����Ƃ��A�e�X�g���ɗ�O����������ƃe�X�g���� catch ����Ȃ��s����C��</li>
    </ul>
  </li>
  <li>v0.21.0.1
    <ul>
      <li>IUTEST_*_NO_FATAL_FAILURE ��ǉ�</li>
      <li>STRCASEEQ, STRCASENE �� ASSERT �ł����g���Ȃ����������C��</li>
      <li>IUTEST_*_PRED5 ���R���p�C���G���[�ɂȂ�����C��</li>
      <li>INFORM �}�N�����ꕔ�R���p�C���G���[�ɂȂ�����C��</li>
      <li>gcc �ŗ�O���g���邩�ǂ����̔��肪�t�ɂȂ��Ă��������C��</li>
      <li>�A�T�[�V�����}�N���ɓn�������̏o�͂��C��</li>
      <li>Visual Studio 11 �Ή�</li>
      <li>clang�Ή�</li>
      <li>�T���v���\�[�X���C��</li>
    </ul>
  </li>
  <li>v0.20.0.0
    <ul>
      <li>--iutest_filter ���g�p�����Ƃ��ɁA���s�e�X�g�o�͂��o�Ȃ��s����C��</li>
      <li>�e�X�g�A�e�X�g�P�[�X�����̎擾�֐����A���s���ĂȂ����̂��܂߂Ă��Ȃ������s����C��</li>
      <li>�e�X�g�A�e�X�g�P�[�X�̎��s�����i���s�\��j�����̎擾�֐���ǉ�</li>
      <li>IUTEST_*_STREQ ���A�������r�}�N���� NULL ��n�����ꍇ�ɗ�O����������s����C��</li>
      <li>IUTEST_RUN_ALL_TESTS �̖߂�l���Ԉ���Ă����s����C��</li>
    </ul>
  </li>
  <li>v0.19.0.0
    <ul>
      <li>�C�x���g���X�i�[�� RecordProperty ���̃C�x���g��ǉ�</li>
      <li>google mock �Ή�</li>
      <li>IUTEST_*_STRCASE* �� std::string �����̂܂܎g����悤�ɏC��</li>
      <li>rvalue reference �Ή�</li>
    </ul>
  </li>
  <li>v0.18.1.1
    <ul>
      <li>On*End �C�x���g�́A���X�g�̌�납����s����悤�ɕύX</li>
      <li>�x���p�i���s�ɂȂ�Ȃ��j�e�X�g IUTEST_INFORM_*** �}�N����ǉ�</li>
      <li>iutest::TestPartResult �̃C���^�[�t�F�C�X���C��</li>
      <li>�G���[�o�͂� Actual �� Expected ���t�ɂȂ��Ă����s����C��</li>
      <li>char �������� unsigned char �� 0 �����b�Z�[�W�o�͂���ۂɃk�������ɂȂ�Ȃ��悤�ɏC��</li>
      <li>�^�[�~�i���̐F���o�͏������C��</li>
      <li>Visual Studio �ȊO�Ńr���h�����ꍇ�̊��ϐ��ɑΉ�</li>
      <li>IUTEST_ASSERT_EQ �̃G���[�o�͂��A Actual �� Expected ���t�ɂȂ��Ă����s����C��</li>
    </ul>
  </li>
  <li>v0.17.0.0
    <ul>
      <li>.h ���� .hpp �ɕύX</li>
      <li>gtest �̃R�}���h���C�������ɑΉ�</li>
      <li>--iutest_filter �I�v�V������ *Test*-*TestA* �̂悤�ɏ��O�t�B���^���������Ƃ��ɐ��������삵�Ȃ��s����C��</li>
    </ul>
  </li>
  <li>v0.16.1.1
    <ul>
      <li>iutest::InitIrisUnitTest �� vector �Ή�</li>
      <li>NaCl, ARM �Ή�</li>
      <li>RecordProperty �� template �Ή�</li>
    </ul>
  </li>
  <li>v0.16.0.2
    <ul>
      <li>�^�A�T�[�V���� �Ή�</li>
      <li>RecoredProperty �Ή�</li>
      <li>iutest::Combine �Ή�/li>
      <li>�^���p�����[�^�������e�X�g<�ɑΉ�/li>
      <li>googletest �Ƃ̐؂�ւ��Ή�</li>
      <li>googletest �Ƃ̍��ق��z��</li>
      <li>�v���I�Ȏ��s���� throw ����I�v�V�����Ή�( --iutest_throw_on_failure=<0|1> )</li>
      <li>�o�ߎ��Ԃ̏o�̓I�v�V�����Ή�( --iutest_print_time=<0|1> )</li>
      <li>���s����e�X�g�̑I���I�v�V�����Ή�( --iutest_filter=selection )</li>
      <li>iutest::PrintToString �Ή�</li>
      <li>IUTEST_FLAG �}�N���ɂ��I�v�V�����w��ɑΉ�</li>
      <li>�J��Ԃ��I�v�V�����Ή�( --iutest_repeat=count )</li>
      <li>�C�x���g���X�i�[�Ή�</li>
      <li>�O���[�o�����Z�b�g�ɑΉ�(iutest::AddGlobalTestEnvironment)</li>
      <li>���������e�X�g�p�ɏq��A�T�[�V�����̃w���p�[��ǉ�(iuutil::CmpHelperOR)</li>
      <li>�^�t���e�X�g�Ή�</li>
      <li>�e�X�g�ɗ��������@�\��ǉ�( genrand )</li>
      <li>���ϐ��ł̃e�X�g�I�v�V�����w��ɑΉ�</li>
      <li>DISABLED�e�X�g���s�I�v�V�����Ή�( --iutest_also_run_disabled_tests )</li>
      <li>��O�L���b�`�I�v�V�����Ή�( --iutest_catch_exceptions=<0|1> )</li>
      <li>���s���u���[�N�I�v�V�����Ή�( --iutest_break_on_failure )</li>
      <li>�V���b�t���e�X�g�Ή�</li>
      <li>�o�̓J���[�I�v�V�����Ή�( --iutest_color=<yes|no|auto> )</li>
      <li>�w���v�I�v�V�����Ή�( --help )</li>
      <li>�p�����[�^�e�X�g�Ή�</li>
      <li>DISABLED_ �ɑΉ�</li>
      <li>xml �o�͂ɑΉ�</li>
    </ul>
  </li>
</ul>
*/

#endif
